#pragma once

#include<string>
#include<list>
#include"EffectElementPram.h"

namespace htAudio
{
	class EffectElementManager
	{
	public:
		EffectElementManager();
		~EffectElementManager();

		// EffectParameterの取得
		EffectElementPram* GetElementPram(std::string _elementpramname);

	private:
		// 取得の際見つからなかった場合に検索する処理
		EffectElementPram* SerchExternalFileElementPram();
		// 見つかった場合は新しく要素を追加する
		EffectElementPram* CreateElementPram();

		std::list<EffectElementPram*> ParameterList; //ポインタを共有して数値を共有します

	};
}