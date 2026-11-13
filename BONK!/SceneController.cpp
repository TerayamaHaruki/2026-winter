#include "SceneController.h"
#include "Scene.h"

void SceneController::ResetScene(std::shared_ptr<Scene> newScene)
{
	m_scenes.clear();
	m_scenes.push_back(newScene);
}

void SceneController::ChangeScene(std::shared_ptr<Scene> newScene)
{
	if (m_scenes.empty())
	{
		m_scenes.push_back(newScene);
		return;
	}
	// 一番上のシーンを入れ替える
	m_scenes.back() = newScene;
}

void SceneController::PushScene(std::shared_ptr<Scene> newScene)
{
	m_scenes.push_back(newScene);
}

void SceneController::PopScene()
{
	// シーンが1つしかないときは外さない
	if (m_scenes.size() <= 1)
	{
		return;
	}
	m_scenes.pop_back();
}

void SceneController::Update(Input& input)
{
	if (m_scenes.empty())
	{
		return;
	}
	// 一番上のシーンだけ更新する(下にあるゲームは止まる)
	m_scenes.back()->Update(input);
}

void SceneController::Draw()
{
	for (auto& scene : m_scenes)
	{
		scene->Draw();
	}
}
