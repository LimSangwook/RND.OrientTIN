#include "TinOrientDBHalfEdge.h"
#include "TinOrientDBStorage.h"
#include "../BaseStorage/ITinVertex.h"
#include "TinOrientDBVertex.h"
#include <assert.h>

CTinOrientDBStorage* GetDB() {
	return CTinOrientDBStorage::GetInstance();
}

CTinOrientDBHalfEdge::CTinOrientDBHalfEdge(RID strRID)
{
	m_RID = strRID;
	m_RIDVertex = "0";
	m_RIDPair = "0";
	m_RIDCCW = "0";
	m_RIDCW = "0";
}

CTinOrientDBHalfEdge::~CTinOrientDBHalfEdge()
{
}

void CTinOrientDBHalfEdge::_Update()
{
	CTinOrientDBStorage::GetInstance()->UpdateHalfEdge(this);
}

ITinVertex* CTinOrientDBHalfEdge::GetVertex()
{
	return	GetDB()->GetVertex(m_RIDVertex);
}

ITinHalfEdge* CTinOrientDBHalfEdge::GetPairEdge()
{
	return GetDB()->GetHalfEdge(m_RIDPair);
}

ITinHalfEdge* CTinOrientDBHalfEdge::GetCCWEdge()
{
	return GetDB()->GetHalfEdge(m_RIDCCW);
}

ITinHalfEdge* CTinOrientDBHalfEdge::GetCWEdge()
{
	return GetDB()->GetHalfEdge(m_RIDCW);
}

void CTinOrientDBHalfEdge::SetVertex(ITinVertex* pVertex)
{
	CTinOrientDBVertex* pDBVertex = dynamic_cast<CTinOrientDBVertex*>(pVertex);
	assert(pDBVertex);
	m_RIDVertex = pDBVertex->GetRID();

	CTinOrientDBHalfEdge* pPair = (CTinOrientDBHalfEdge*)GetDB()->GetHalfEdge(m_RIDPair);
	if (pPair != NULL){
		pPair->SetRIDEndVertex(m_RIDVertex);
		//pPair->_Update();
	}
	_Update();
}

void CTinOrientDBHalfEdge::SetPairEdge(ITinHalfEdge* pEdge)
{
	CTinOrientDBHalfEdge* pDBEdge = dynamic_cast<CTinOrientDBHalfEdge*>(pEdge);
	assert(pDBEdge);
	m_RIDPair = pDBEdge->GetRID();
	m_RIDEndVertex = pDBEdge->GetRIDVertex();
	((CTinOrientDBHalfEdge*) (pEdge))->SetRIDEndVertex(m_RIDVertex);
	_Update();
}

void CTinOrientDBHalfEdge::SetCCWEdge(ITinHalfEdge* pEdge)
{
	CTinOrientDBHalfEdge* pDBEdge = dynamic_cast<CTinOrientDBHalfEdge*>(pEdge);
	assert(pDBEdge);
	m_RIDCCW = pDBEdge->GetRID();
	_Update();
}

void CTinOrientDBHalfEdge::SetCWEdge(ITinHalfEdge* pEdge)
{
	CTinOrientDBHalfEdge* pDBEdge = dynamic_cast<CTinOrientDBHalfEdge*>(pEdge);
	assert(pDBEdge);
	m_RIDCW = pDBEdge->GetRID();
	_Update();
}

