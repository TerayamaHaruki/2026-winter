#include "Force.h"
#include"Player.h"
#include"../Application.h"
#include<DxLib.h>
#include<algorithm>

constexpr float force_radius = 16.0f;
constexpr int force_img_width = 64;
constexpr int force_img_height = 64;
constexpr int force_img_scale = 1.0f;
constexpr int force_anim_num = 3;
constexpr int force_anim_interval = 5;

constexpr float force_coming_speed = 2.5f;
constexpr float force_kick_speed = 8.0f;
//constexpr float force_kick_distance = 250.0f;
constexpr float force_separate_distance = 250.0f;

//フォースがある程度近づくと吸着する半径
constexpr float force_vacuum_radius = 50.0f;

constexpr float player_scale = 2.0f;
constexpr int player_img_width = 26;

//くっついてる状態
void Force::AttachedUpdate()
{
	if (isDead_)return;
	if (player_.expired())return;
	
	//意図的にキックされるまではプレイヤーにくっついたまま
	auto& pos = GetPosition();
	//プレイヤーの座標に決められたオフセットだけ離してくっついておく
	pos = player_.lock()->GetPosition() + attachedForceOffset_;
}

void Force::SeparatedUpdate()
{
	if (isDead_)return;
	if (player_.expired())return;

	auto& pos = GetPosition();
	const auto& ppos = player_.lock()->GetPosition();

	//距離が離れている場合は、Y座標のみゆっくり合わせてくるかつ
	//X方向に一定の距離を保とうとします
	//ただしプレイヤーから近づいてきたときは離れていかない
	if (attachedForceOffset_.Length() > 0.0f) {
		Vector2 vel = {};
		vel.y = ppos.y - pos.y;//Y方向を合わせてくる
		vel.x = -attachedForceOffset_.x;//距離を詰めてこようとする
		// 離れてる状態で一定の距離を保とうとする
		if (fabsf(ppos.x - pos.x) < force_separate_distance) {
			vel.x = 0.0f;
		}
		//速度を正規化したうえで座標に反映する
		pos += vel.Normalized() * force_coming_speed;
	}


	//プレイヤーが自分から浮いてるフォースに近寄っていくと吸着し
	//AttachedUpdate(くっつく)に遷移する
	if (GetDistance(pos, ppos) <= force_vacuum_radius) {
		AttachForce();
		return;
	}
}

void Force::AttachForce()
{
	auto& pos = GetPosition();
	const auto& ppos = player_.lock()->GetPosition();
	//フォースがちょっとでもプレイヤーの後ろなら後ろにくっつき
	if (pos.x < ppos.x) {
		//後ろにくっつける(マイナス方向)
		attachedForceOffset_ = { -(player_img_width * player_scale + force_radius) / 2.0f ,0.0f };
	}
	else {//そうでないなら前にくっつく(プラス方向)
		attachedForceOffset_ = { (player_img_width * player_scale + force_radius) / 2.0f ,0.0f };
	}
	//状態を「くっついてる状態」に遷移させる
	update_ = &Force::AttachedUpdate;
}

void Force::ComingUpdate()
{
	//プレイヤーにゆっくり近づいていく(プレイヤーにホーミング)
	auto& pos = GetPosition();
	if (player_.expired())return;

	const auto& ppos = player_.lock()->GetPosition();
	//プレイヤーへのベクトルを計算し、その方向に移動
	pos+=(ppos - pos).Normalized()* force_coming_speed;

	//ある程度以上近づいたら「くっついてる状態」に遷移する
	if (GetDistance(pos, ppos) <= force_vacuum_radius) {
		AttachForce();
		return;
	}
}

void Force::KickingUpdate()
{
	constexpr float attenuation = 0.97f;
	constexpr float threshold = 0.1f;
	const auto& wsize = Application::GetInstance().GetWindowSize();
	auto& pos = GetPosition();
	pos += vel_;//キックされたときのスピードのまま進む
	vel_ *= attenuation;//キック速度の減衰
	if (vel_.Length() < threshold) {//一定速度より小さくなったらもう次の状態に遷移する
		vel_ = {};
		update_ = &Force::SeparatedUpdate;
	}
	//ある程度離れたら移動をやめ、離れてる状態(初期状態)に遷移する
	//if (force_kick_distance <= fabsf(kickStartPos_.x - pos.x) ||  
	//	(pos.x<=0+force_radius || wsize.w-force_radius<=pos.x)) {
	//	pos.x = std::clamp(pos.x, force_radius, wsize.w - force_radius);
	//	update_ = &Force::SeparatedUpdate;
	//	return;
	//}

}

Force::Force(int handle, std::weak_ptr<Player> player, std::weak_ptr<GameScene> gs) :
	Actor({}, force_radius),
	handle_(handle),
	player_(player),
	gameScene_(gs)

{
	isDead_ = true;
	type_ = ActorType::force;
	const auto& wsize = Application::GetInstance().GetWindowSize();
	auto& pos = GetPosition();
	pos = { wsize.w / 2.0f,wsize.h / 2.0f };
}

void Force::Update()
{
	(this->*update_)();
	++frame_;
}

void Force::Draw()
{
	if (isDead_)return;
	auto& pos = GetPosition();
	int idx = (frame_ / force_anim_interval) % force_anim_num;
	DrawRectRotaGraph(pos.x, pos.y,
		idx * force_img_width, 0,
		force_img_width, force_img_height,
		force_img_scale, 0.0f,
		handle_, true);
	GetCollision()->Draw();
}

void Force::OnHit(const std::shared_ptr<Actor> actor)
{

}

void Force::Run()
{
	isDead_ = false;
}

void Force::Action()
{
	//明確にくっついてる状態か離れてる状態のときにしか
	//Actionは有効ではない
	
	//現在の状態を見て、離すか寄せるかを決定する
	if (update_ == &Force::AttachedUpdate) {//くっついていれば
		Kick();//離す
	}
	else if(update_==&Force::SeparatedUpdate){//離れていれば
		ComeHere();//寄せる
	}
	//キックしている状態と寄せている状態のときはアクションは無効
}

bool Force::IsBackAttached() const
{
	return update_ == &Force::AttachedUpdate && attachedForceOffset_.x < 0.0f;
}

void Force::Kick()
{
	//フォースを「離れる方向」にポーンと飛ばします
	//キックは現在くっついてる状態(AttachedUpdate)じゃないと有効ではない
	auto& pos = GetPosition();
	//まず初速を与えます
	vel_ = attachedForceOffset_.Normalized() * force_kick_speed;
	kickStartPos_ = pos;//どれくらいキックしてから離れたかを観測するために記録
	update_ = &Force::KickingUpdate;
}

void Force::ComeHere()
{
	//離れてるときにのみ、引き寄せるのは有効
	if (update_ == &Force::SeparatedUpdate) {
		if (player_.expired())return;

		auto& pos = GetPosition();
		auto& ppos = player_.lock()->GetPosition();
		//プレイヤーに近づくように動く
		vel_ = (ppos - pos).Normalized() * force_coming_speed;
		update_ = &Force::ComingUpdate;
		return;
	}
}
