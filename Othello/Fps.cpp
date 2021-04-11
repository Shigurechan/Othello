#include "Fps.hpp"

int Fps::count = 0;
int Fps::startCount = 0;

Fps::Fps()
{
	startTime = 0;
	count = 0;
	
}

//�X�V
void Fps::Update() 
{

	startCount++;

	//1�t���[���ڂȂ玞�����L��
	if (count == 0) 
	{ 
		startTime = GetNowCount();
	}

	//60�t���[���ڂȂ畽�ς��v�Z����
	if (count == N) 
	{ 
		startTime = GetNowCount();
		count = 0;
	}

	count++;
	
}

//���݂̃t���[�����擾
int Fps::getFrame() 
{
	return count;
}

//�o�߃t���[�����擾
int Fps::getElapsed()
{
	return startCount;
}



//�ҋ@
void Fps::Wait() 
{
	int tookTime = GetNowCount() - startTime;		//������������
	int waitTime = (count * 1000 / FPS) - tookTime;	//�҂ׂ�����

	if (waitTime > 0)
	{
		Sleep(waitTime);	//�ҋ@
	}

	//�o�߃t���[��
	if (startCount > 60000) 
	{
		startCount = 0;
	}
}