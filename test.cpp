// ここにサンプルプログラムをペーストしてください
// 初期状態では LoadGraphScreen のサンプルプログラムが入力されています。
#include "DxLib.h"
#include "SeanManager.h"
#include "SeanTest.h"

#define _SeanMaxSize 32768

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				 LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(true);			//ウィンドウモード.
	SetGraphMode(640, 480, 32);	//画面サイズ設定.
	SetUseTransColor(FALSE);		//黒を透過しない.
	SetAlwaysRunFlag(TRUE);			//ウィンドウが非アクティブでもゲーム進行.
	SetWindowText("testDeSu");		//ゲームタイトル.
	SetDoubleStartValidFlag(false);	//多重起動禁止.
	SetMainWindowClassName("testDeSu");//DxLibの衝突回避用namespase.
	SetWaitVSyncFlag(FALSE);		//フレームtレート解除（現在自分で実装）巣のやつだとなぜかアクティブ時４５.
	if( DxLib_Init() == -1 )	// ＤＸライブラリ初期化処理
	{
		 return -1;				// エラーが起きたら直ちに終了
	}
	MyGT::SeanManager<_SeanMaxSize>* seanM = MyGT::SeanManager<_SeanMaxSize>::get_instance();
	seanM->push_back<SeanTest>();
	seanM->start();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		seanM->update();
	}

	// ＢＭＰ画像の表示
	//LoadGraphScreen( 0 , 0 , "test1.bmp" , TRUE ) ;
	seanM->pop_back();

	WaitKey() ;					// キーの入力待ち((7-3)『WaitKey』を使用)

	DxLib_End() ;				// ＤＸライブラリ使用の終了処理


	return 0 ;					// ソフトの終了
}

//
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	LONGLONG NowTime;
//	LONGLONG Time;
//	float x, add;
//	float DeltaTime;
//	int FPS;
//	int FPSCounter;
//	LONGLONG FPSCheckTime;
//
//	// ウインドウモードで起動
//	ChangeWindowMode(TRUE);
//
//	// ScreenFlip を実行しても垂直同期信号を待たない
//	SetWaitVSyncFlag(FALSE);
//
//	// ＤＸライブラリの初期化
//	if (DxLib_Init() < 0) return -1;
//
//	// 描画先を裏画面にする
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	// 座標を初期化
//	x = 0.0f;
//
//	// 速度を初期化( 1秒間に移動するドット数 )
//	add = 200.0f;
//
//	// システム時間を取得しておく
//	Time = GetNowHiPerformanceCount();
//
//	// 最初の経過時間は仮に 0.000001f 秒にしておく
//	DeltaTime = 0.000001f;
//
//	// FPS計測関係の初期化
//	FPSCheckTime = GetNowHiPerformanceCount();
//	FPS = 0;
//	FPSCounter = 0;
//
//	// メインループ
//	while (ProcessMessage() == 0)
//	{
//		// 経過時間を考慮した移動( DeltaTime を掛ける )
//		x += add * DeltaTime;
//		if (x < 0.0f)
//		{
//			x = 0.0f;
//			add = -add;
//		}
//		if (x > 640.0f)
//		{
//			x = 640.0f;
//			add = -add;
//		}
//
//		// 画面のクリア
//		ClearDrawScreen();
//
//		// 四角形の描画
//		DrawBox((int)x, 240 - 32, (int)x + 64, 240 + 32, GetColor(255, 255, 255), TRUE);
//
//		// FPSの描画
//		DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS:%d", FPS);
//
//		// 裏画面の内容を表画面に反映
//		ScreenFlip();
//
//		// 現在のシステム時間を取得
//		NowTime = GetNowHiPerformanceCount();
//
//		// 前回取得した時間からの経過時間を秒に変換してセット
//		// ( GetNowHiPerformanceCount で取得できる値はマイクロ秒単位なので 1000000 で割ることで秒単位になる )
//		DeltaTime = (NowTime - Time) / 1000000.0f;
//
//		// 今回取得した時間を保存
//		Time = NowTime;
//
//		// FPS関係の処理( 1秒経過する間に実行されたメインループの回数を FPS とする )
//		FPSCounter++;
//		if (NowTime - FPSCheckTime > 1000000)
//		{
//			FPS = FPSCounter;
//			FPSCounter = 0;
//			FPSCheckTime = NowTime;
//		}
//	}
//
//	// ＤＸライブラリの後始末
//	DxLib_End();
//
//	// ソフトの終了
//	return 0;
//}
