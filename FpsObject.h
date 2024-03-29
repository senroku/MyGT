#pragma once
#include "DxLib.h"
#include "GameObject.h"


namespace MyGT {
    constexpr int Frame = 60;
    struct FpsObject:public GameObject,Sprite
    {
        FpsObject() :mStartTime(0), mCount(0), mFps(0.0f){}

		void update() {
			if (mCount == 0) { //1フレーム目なら時刻を記憶
				mStartTime = GetNowCount();
			}
			if (mCount == N) { //60フレーム目なら平均を計算する
				int t = GetNowCount();
				mFps = 1000.f / ((t - mStartTime) / (float)N);
				mCount = 0;
				mStartTime = t;
			}
			mCount++;
			Draw();
			//Wait();
		}

		void Draw() {
			DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mFps);
		}

		void Wait() {
			int tookTime = GetNowCount() - mStartTime;	//かかった時間
			int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
			if (waitTime > 0) {
				Sleep(waitTime);	//待機
			}
		}
    private:
        int mStartTime;         //測定開始時刻
        int mCount;             //カウンタ
        float mFps;             //fps
        static const int N = 60;//平均を取るサンプル数
        static const int FPS = 60;	//設定したFPS
		char a[8];
    };


	using FpsManager = GameObjectManager<1,FpsObject>;

}