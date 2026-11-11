#include "FileLoader.h"
#include<DxLib.h>
#include<cassert>
#include<algorithm>

FileLoader::Asset::~Asset()
{
	//アセットが削除されるときにハンドルも自動削除しておく
	switch (fileType) {
	case FileType::graphic:
		DeleteGraph(handle);
		break;
	case FileType::sound:
		DeleteSoundMem(handle);
		break;
	default:
		break;
	}
}

int FileLoader::LoadGraph(const std::wstring& path, AssetType type)
{
	//ロード済みのアセット
	if (assets_.contains(path)) {
		return assets_[path]->handle;
	}
	//まだロード済みではないアセット
	int h = DxLib::LoadGraph(path.c_str());
	assert(h>=0);
	auto asset = std::make_shared<Asset>();
	asset->fileType = FileType::graphic;
	asset->type = type;//continuosかtemporaryか
	asset->handle = h;//ファイルハンドル
	assets_[path] = asset;
	return h;
}

int FileLoader::LoadSound(const std::wstring& path, AssetType type)
{
	if (assets_.contains(path)) {//もしロード済みなら
		return assets_[path]->handle;//そのハンドルを返す
	}
	//まだロード済みではないなら、ロードして登録そしてハンドルを返す
	auto asset=std::make_shared<Asset>();
	auto h = LoadSoundMem(path.c_str());
	assert(h >= 0);
	asset->handle = h;
	asset->type = type;
	asset->fileType = FileType::sound;
	assets_[path] = asset;
	return h;
}

void FileLoader::DeleteTemporalAssets()
{
	std::erase_if(assets_,
					[](const auto& asset) {
						return asset.second->type == AssetType::temporary;//一時オブジェクトだったら削除対象
					});
}
