#include "Input.hpp"


// �R���X�g���N�^
Input::Input()
{
    //�L�[��Ԕz���������
    for (int i = 0; i < 256; i++)
    {
        Key[i] = 0;
    }
}

//�L�[���͏�Ԃ��X�V
void Input::Update()
{
    char tmpKey[256] = { 0 };           // ���݂̃L�[�̓��͏�Ԃ��i�[����
    GetHitKeyStateAll(tmpKey);          // �S�ẴL�[�̓��͏�Ԃ𓾂�
    for (int i = 0; i < 256; i++) {
        if (tmpKey[i] != 0) {           // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
            Key[i]++;                   // ���Z
        }
        else {

            // ������Ă��Ȃ����
            Key[i] = 0;   // 0�ɂ���
        }
    }
}

//�L�[��������������
bool Input::getKeyDown(unsigned char KeyCode)
{
    if (Key[KeyCode] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//�L�[�������Ă��鎞
int Input::getKeyDownHold(unsigned char KeyCode)
{

    return Key[KeyCode];
}

//�@�f�X�g���N�^
Input::~Input()
{

}

