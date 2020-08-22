// �����ɃT���v���v���O�������y�[�X�g���Ă�������
// ������Ԃł� LoadGraphScreen �̃T���v���v���O���������͂���Ă��܂��B
#include "DxLib.h"
#include "SeanManager.h"
#include "SeanTest.h"

#define _SeanMaxSize 32768

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
				 LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(true);
	if( DxLib_Init() == -1 )	// �c�w���C�u��������������
	{
		 return -1;				// �G���[���N�����璼���ɏI��
	}
	SeanManager<_SeanMaxSize>* seanM = SeanManager<_SeanMaxSize>::get_instance();
	seanM->push_back<SeanTest>();
	seanM->push_back<SeanTest>();
	seanM->start();
	seanM->update();
	seanM->pop_back();

	// �a�l�o�摜�̕\��
	LoadGraphScreen( 0 , 0 , "test1.bmp" , TRUE ) ;

	WaitKey() ;					// �L�[�̓��͑҂�((7-3)�wWaitKey�x���g�p)

	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������


	return 0 ;					// �\�t�g�̏I��
}
