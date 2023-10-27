//============================================
//
//	�G�t�F�N�g���� [EffectMovePolygon.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _EFFECTMOVEPOLYGON_H_
#define _EFFECTMOVEPOLYGON_H_

#include "main.h"
#include "objectBillboard.h"

//�I�u�W�F�N�g�v���C���[�N���X
class CEffectMovePolygon : public CObjectBillboard
{
public:

	CEffectMovePolygon(int nPriority = 4);
	~CEffectMovePolygon();

	static CEffectMovePolygon *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetRadius(float Radius) { m_fSetRadius = Radius; }
	float GetRadius(void) { return m_fDel; }
	void SetDel(float Del) { m_fDel = Del; }
	float GetDel(void) { return m_fDel; }
	void SetColer(D3DXCOLOR Coler) { m_col = Coler; }
	D3DXCOLOR GetColer(void) { return m_col; }
	void SetLife(int Life) { m_nLife = Life; }
	int GetLife(void) { return m_nLife; }
	int GetIdx(void) { return m_nIdxTexture; }

private:
	D3DXVECTOR3 m_CenterPos;				//���S�̍��W	
	D3DXVECTOR3 m_VtxPos[4];				//���_�̍��W	
	int m_nIdxTexture;						//�e�N�X�`���̔ԍ�
	static LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_move;						//�ړ���	
	float m_fRadius;						//���a(�傫��)	
	float m_fSetRadius;						//�ŏI�I�Ȕ��a(�傫��)	
	float m_fDel;							//���a�����������Ă����l
	D3DXCOLOR m_col;						//�F
	int m_nLife;							//����
	float m_fStartRadius;					//�J�n���̑傫��
	bool m_bStart;							//�J�n�t���O
	bool m_bCenter;							//���ԃt���O
	bool m_bSet;							//�o���t���O
};
#endif