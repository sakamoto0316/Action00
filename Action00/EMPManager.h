//============================================
//
//	�G�t�F�N�g���� [EffectMovePolygon.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _EMPMANGER_H_
#define _EMPMANGER_H_

#include "main.h"
#include "objectBillboard.h"

//�I�u�W�F�N�g�v���C���[�N���X
class CEMPManager : public CObject
{
public:

	CEMPManager(D3DXVECTOR3 pos, float fRadius, float fDel, int nSetCount, int nType, int nPriority = 4);
	~CEMPManager();

	static CEMPManager *Create(D3DXVECTOR3 pos, float fRadius, float fDel, int nSetCount, int nType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetMoveParticle(D3DXVECTOR3 pos, float fRadius, float fDel, int nSetCount, int nType);

private:
	int m_nType;					//���
	int m_nPSetWave;				//�o���E�F�[�u
	int m_nPSetCount;				//�o���J�E���g
	int m_nPSetCountMax;			//�o���J�E���g�̍ő�l
	D3DXVECTOR3 m_Ppos;				//�ʒu
	float m_nPRadius;				//�傫��
	float m_nPDel;					//���ő��x
};
#endif