#include "Cell.h"

Cell::Cell()
	: m_cellFlag{ false }, m_cellHide{ true }, m_cellType{ CellType::None }
{
}

Cell::Cell(bool cellFlag, bool cellHide, CellType cellType)
	: m_cellFlag{ cellFlag }, m_cellHide{ cellHide }, m_cellType{ cellType }
{
}

void Cell::SetCellHide()
{
	m_cellHide = false;
}

void Cell::SetCellFlag()
{
	if (this->isHidden())
		this->m_cellFlag = !this->m_cellFlag;
}

Cell::~Cell()
{
	m_cellType = CellType::None;
}

void Cell::SetCellType(CellType cellType)
{
	m_cellType = cellType;
}

Cell& Cell::operator=(const Cell& other)noexcept
{
	if (this != &other)
	{
		this->m_cellFlag = other.m_cellFlag;
		this->m_cellHide = other.m_cellHide;
		this->m_cellType = other.m_cellType;
	}
	return*this;
}

Cell& Cell::operator=(Cell&& other)noexcept
{
	if (this != &other)
	{
		this->m_cellFlag = other.m_cellFlag;
		this->m_cellHide = other.m_cellHide;
		this->m_cellType = other.m_cellType;
		new(&other) Cell();
	}
	return *this;
}

Cell::Cell(const Cell& other)
{
	*this = other;
}

Cell::Cell(Cell&& other)
{
	*this = std::move(other);
}

const uint8_t Cell::GetHeight()
{
	return Cell::m_cellHeight;
}

bool Cell::isHidden()
{
	return m_cellHide == true;
}

bool Cell::IsFlag()
{
	return m_cellFlag == true;
}

bool Cell::operator==(const Cell& other)
{
	if (this->m_cellFlag == other.m_cellFlag && this->m_cellHide == other.m_cellHide && this->m_cellType == other.m_cellType)
		return true;
	return false;
}

CellType Cell::GetType() const
{
	return m_cellType;
}

std::ostream& operator<<(std::ostream& write, const Cell& other)
{
	write << "Flag added: " << static_cast<bool>(other.m_cellFlag) << std::endl;
	write << "Is hidden: " << static_cast<bool>(other.m_cellHide) << std::endl;
	write << "Cell type: " << ConvertCellTypeToString(other.m_cellType) << std::endl;
	return write;
}
