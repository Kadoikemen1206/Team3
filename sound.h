//**************************************************
//
// sound.h
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _SOUND_H_	//このマクロ定義がされてなかったら
#define _SOUND_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include <xaudio2.h>

//==================================================
// 定義
//==================================================
class CSound
{
	/* ↓定義↓ */
public:
	enum ELabel
	{
		LABEL_NONE = -1,
		LABEL_BGM_TITLE = 0,	// タイトル
		LABEL_BGM_GAME,			// ゲーム
		LABEL_BGM_RESULT,		// リザルト
		LABEL_SE_CHAKUCHI_01,	// 着地音_01
		LABEL_SE_CHAKUCHI_02,	// 着地音_02
		LABEL_SE_COUNTDOWN,		// カウントダウン
		LABEL_SE_ENTER_KEY_01,	// 決定ボタン_01
		LABEL_SE_ENTER_KEY_02,	// 決定ボタン_02
		LABEL_SE_ENTER_KEY_03,	// 決定ボタン_03
		LABEL_SE_GAMECLEAR,		// ゲームクリア
		LABEL_SE_GIMIKKU_CLEAR,	// ギミッククリア
		LABEL_SE_HAGURUMA_KAITEN,	// 歯車と回転
		LABEL_SE_HASHIRI,		// 走る音
		LABEL_SE_HIKIZURI,		// 引きずり音
		LABEL_SE_JUMP_01,		// ジャンプ音_01
		LABEL_SE_JUMP_02,		// ジャンプ音_02
		LABEL_SE_NEGIMAKI,		// ねじ巻き音
		LABEL_SE_RAKKA,			// 落下音
		LABEL_SE_RESPAWN,		// リスポーン音
		LABEL_MAX,
	};

	struct SParam
	{
		char *pFileName;	// ファイル名
		int loop;			// ループ
	};

	static const SParam PARAM[];	// パラメータの情報

	/* ↓メンバ関数↓ */
public:
	CSound();	// デフォルトコンストラクタ
	~CSound();	// デストラクタ

public:
	HRESULT Init(HWND hWnd);
	void Uninit();
	HRESULT Play(ELabel sound);
	void Stop(ELabel label);
	void Stop();

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);	// チャンクのチェック
	HRESULT LoadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// チャンクデータの読み込み

	/* ↓メンバ変数↓ */
private: 
	IXAudio2* m_pXAudio2;							// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;		// マスターボイス
	IXAudio2SourceVoice* m_pSourceVoice[LABEL_MAX];	// ソースボイス
	BYTE* m_pDataAudio[LABEL_MAX];					// オーディオデータ
	DWORD m_sizeAudio[LABEL_MAX];					// オーディオデータサイズ
};

#endif // !_SOUND_H_
