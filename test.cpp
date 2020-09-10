// �����ɃT���v���v���O�������y�[�X�g���Ă�������
// ������Ԃł� LoadGraphScreen �̃T���v���v���O���������͂���Ă��܂��B
#include "DxLib.h"
#include "SeanManager.h"
#include "SeanTest.h"

#define _SeanMaxSize 32768

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				 LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(true);			//�E�B���h�E���[�h.
	SetGraphMode(640, 480, 32);	//��ʃT�C�Y�ݒ�.
	SetUseTransColor(FALSE);		//���𓧉߂��Ȃ�.
	SetAlwaysRunFlag(TRUE);			//�E�B���h�E����A�N�e�B�u�ł��Q�[���i�s.
	SetWindowText("testDeSu");		//�Q�[���^�C�g��.
	SetDoubleStartValidFlag(false);	//���d�N���֎~.
	SetMainWindowClassName("testDeSu");//DxLib�̏Փˉ��pnamespase.
	SetWaitVSyncFlag(FALSE);		//�t���[��t���[�g�����i���ݎ����Ŏ����j���̂���ƂȂ����A�N�e�B�u���S�T.
	if( DxLib_Init() == -1 )	// �c�w���C�u��������������
	{
		 return -1;				// �G���[���N�����璼���ɏI��
	}
	MyGT::SeanManager<_SeanMaxSize>* seanM = MyGT::SeanManager<_SeanMaxSize>::get_instance();
	seanM->push_back<SeanTest>();
	seanM->start();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		seanM->update();
	}

	// �a�l�o�摜�̕\��
	//LoadGraphScreen( 0 , 0 , "test1.bmp" , TRUE ) ;
	seanM->pop_back();

	WaitKey() ;					// �L�[�̓��͑҂�((7-3)�wWaitKey�x���g�p)

	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������


	return 0 ;					// �\�t�g�̏I��
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
//	// �E�C���h�E���[�h�ŋN��
//	ChangeWindowMode(TRUE);
//
//	// ScreenFlip �����s���Ă����������M����҂��Ȃ�
//	SetWaitVSyncFlag(FALSE);
//
//	// �c�w���C�u�����̏�����
//	if (DxLib_Init() < 0) return -1;
//
//	// �`���𗠉�ʂɂ���
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	// ���W��������
//	x = 0.0f;
//
//	// ���x��������( 1�b�ԂɈړ�����h�b�g�� )
//	add = 200.0f;
//
//	// �V�X�e�����Ԃ��擾���Ă���
//	Time = GetNowHiPerformanceCount();
//
//	// �ŏ��̌o�ߎ��Ԃ͉��� 0.000001f �b�ɂ��Ă���
//	DeltaTime = 0.000001f;
//
//	// FPS�v���֌W�̏�����
//	FPSCheckTime = GetNowHiPerformanceCount();
//	FPS = 0;
//	FPSCounter = 0;
//
//	// ���C�����[�v
//	while (ProcessMessage() == 0)
//	{
//		// �o�ߎ��Ԃ��l�������ړ�( DeltaTime ���|���� )
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
//		// ��ʂ̃N���A
//		ClearDrawScreen();
//
//		// �l�p�`�̕`��
//		DrawBox((int)x, 240 - 32, (int)x + 64, 240 + 32, GetColor(255, 255, 255), TRUE);
//
//		// FPS�̕`��
//		DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS:%d", FPS);
//
//		// ����ʂ̓��e��\��ʂɔ��f
//		ScreenFlip();
//
//		// ���݂̃V�X�e�����Ԃ��擾
//		NowTime = GetNowHiPerformanceCount();
//
//		// �O��擾�������Ԃ���̌o�ߎ��Ԃ�b�ɕϊ����ăZ�b�g
//		// ( GetNowHiPerformanceCount �Ŏ擾�ł���l�̓}�C�N���b�P�ʂȂ̂� 1000000 �Ŋ��邱�Ƃŕb�P�ʂɂȂ� )
//		DeltaTime = (NowTime - Time) / 1000000.0f;
//
//		// ����擾�������Ԃ�ۑ�
//		Time = NowTime;
//
//		// FPS�֌W�̏���( 1�b�o�߂���ԂɎ��s���ꂽ���C�����[�v�̉񐔂� FPS �Ƃ��� )
//		FPSCounter++;
//		if (NowTime - FPSCheckTime > 1000000)
//		{
//			FPS = FPSCounter;
//			FPSCounter = 0;
//			FPSCheckTime = NowTime;
//		}
//	}
//
//	// �c�w���C�u�����̌�n��
//	DxLib_End();
//
//	// �\�t�g�̏I��
//	return 0;
//}
