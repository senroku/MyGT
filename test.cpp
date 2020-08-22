// ここにサンプルプログラムをペーストしてください
// 初期状態では LoadGraphScreen のサンプルプログラムが入力されています。
#include "DxLib.h"
#include "SeanManager.h"
#include "SeanTest.h"

#define _SeanMaxSize 32768

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				 LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(true);
	if( DxLib_Init() == -1 )	// ＤＸライブラリ初期化処理
	{
		 return -1;				// エラーが起きたら直ちに終了
	}
	SeanManager<_SeanMaxSize>* seanM = SeanManager<_SeanMaxSize>::get_instance();
	seanM->push_back<SeanTest>();
	seanM->push_back<SeanTest>();
	seanM->start();
	seanM->update();
	seanM->pop_back();

	// ＢＭＰ画像の表示
	LoadGraphScreen( 0 , 0 , "test1.bmp" , TRUE ) ;

	WaitKey() ;					// キーの入力待ち((7-3)『WaitKey』を使用)

	DxLib_End() ;				// ＤＸライブラリ使用の終了処理


	return 0 ;					// ソフトの終了
}
