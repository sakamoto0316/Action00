//============================================
//
//	�G�f�B�b�g [Edit.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _EDIT_H_
#define _EDIT_H_

#include "main.h"
#include "object.h"

#define SET_BLOCK_WIGHT (20)
#define SET_BLOCK_HEIGHT (25)
#define DATA_NAME ("data\\TXT\\ShortMap")	//�X�^�[�g���b�Z�[�W�����邩�ǂ����̊m�F

//�O���錾
class CMapBlock;
class CMapNeedle;
class CMapNeedleUD;
class CMapNeedleLR;
class CMapDoor;
class CMapSwitch;
class CMapPitFloor;
class CMapCannon;
class CMapCheckPoint;

//�}�b�v�N���X
class CEdit
{
public:
	CEdit();
	~CEdit();

	static CEdit *Create();
	void Uninit(void);
	void Update(void);

	void LoadData(char *Name, D3DXVECTOR3 pos);

	D3DXVECTOR3 GetEditPos(void) { return m_EditPos; }
protected:

private:
	void DeleteObject(D3DXVECTOR3 pos);
	void DebugObject(void);
	void SaveData(void);

	static CMapBlock *m_EditBlock;
	static CMapNeedle *m_EditNeedle;
	static CMapNeedleUD *m_EditNeedleUD;
	static CMapNeedleLR *m_EditNeedleLR;
	static CMapDoor *m_EditDoor;
	static CMapSwitch *m_EditSwitch;
	static CMapPitFloor *m_EditPitFloor;
	static CMapCannon *m_EditCannon;
	static CMapCheckPoint *m_EditCheckPoint;
	int ObjectType;
	int m_HeightNumber;			//�c�̔ԍ�
	D3DXVECTOR3 m_EditPos;		//���W
	D3DXVECTOR3 m_EditPos2;		//���W
	bool m_RotChange;			//���W�ƌ����̐؂�ւ�
	int m_RotSelecet;			//�����̐؂�ւ�
	float m_fNeedleMoveWight;	//�Ƃ��̈ړ��͈�
	float m_fNeedleMoveSpeed;	//�Ƃ��̈ړ����x
	int m_nSideCount;				//���E�ړ��̒������J�E���g
};
#endif