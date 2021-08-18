#pragma once
#include <iostream>
#include "CellType.h"
class Cell
{

public:
	Cell();
	Cell(bool, bool, CellType);
	Cell(const Cell&);
	Cell(Cell&&);
	~Cell();
	Cell& operator=(const Cell&)noexcept;
	Cell& operator=(Cell&&)noexcept;

	void SetCellHide();
	void SetCellFlag();
	void SetCellType(CellType);

	static const uint8_t GetHeight();
	CellType GetType()const;

	bool isHidden();
	bool IsFlag();

	bool operator==(const Cell& other);
	friend std::ostream& operator<<(std::ostream&, const Cell&);

private:
	static const uint8_t m_cellHeight = 30;
	bool m_cellFlag;
	bool m_cellHide;
	CellType m_cellType;
	//int m_value;
};

