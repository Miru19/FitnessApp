#include "pch.h"
#include "CppUnitTest.h"
#include <string>

#include "../Minesweeper/Cell.h"
#include "../Minesweeper/Cell.cpp"
#include "../Minesweeper/CellType.h"
#include "../Minesweeper/CellType.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MinesweeperUnitTests
{
	TEST_CLASS(CellTest)
	{
	public:

		TEST_METHOD(CellTypeToString)
		{
			CellType cellType = CellType::Bomb;
			Assert::IsTrue(ConvertCellTypeToString(cellType) == "Bomb");
			cellType = CellType::Empty;
			Assert::IsTrue(ConvertCellTypeToString(cellType) == "Empty");
			cellType = CellType::None;
			Assert::IsTrue(ConvertCellTypeToString(cellType) == "No value");
			cellType = CellType::Number;
			Assert::IsTrue(ConvertCellTypeToString(cellType) == "Number");
		}

		TEST_METHOD(StringToCellType)
		{
			std::string cell = "Bomb";
			Assert::IsTrue(ConvertStringToCellType(cell) == CellType::Bomb);
			cell = "Empty";
			Assert::IsTrue(ConvertStringToCellType(cell) == CellType::Empty);
			cell = "No value";
			Assert::IsTrue(ConvertStringToCellType(cell) == CellType::None);
			cell = "Number";
			Assert::IsTrue(ConvertStringToCellType(cell) == CellType::Number);
		}

		TEST_METHOD(CellConstructor)
		{
			Cell cell;
			Assert::IsTrue(cell.isHidden() == true);
			Assert::IsTrue(cell.IsFlag() == false);
			Assert::IsTrue(cell.GetType() == CellType::None);
		}

		TEST_METHOD(CellConstructorParameters)
		{
			Cell cell(true, true, CellType::Number);
			Assert::IsTrue(cell.isHidden() == true);
			Assert::IsTrue(cell.IsFlag() == true);
			Assert::IsTrue(cell.GetType() == CellType::Number);
		}

		TEST_METHOD(PrintCell)
		{
			Cell cell(false, false, CellType::Bomb);
			std::stringstream stream;
			stream << cell;
			Assert::AreEqual<std::string>("Flag added: 0\nIs hidden: 0\nCell type: Bomb\n", stream.str());
		}

		TEST_METHOD(EqualEqualOperator)
		{
			Cell cell1(true, true, CellType::Number);
			Cell cell2(true, true, CellType::Number);
			Assert::IsTrue(cell1 == cell2);
		}

		TEST_METHOD(EqualOperator)
		{
			Cell cell1(true, true, CellType::Number);
			Cell cell2 = cell1;
			Assert::IsTrue(cell1 == cell2);
		}

		TEST_METHOD(CopyConstructorCell)
		{
			Cell cellTest1(false, false, CellType::Bomb), cellTest2;
			cellTest2 = cellTest1;
			Cell cellTest3(cellTest2);
			Assert::IsTrue(cellTest1 == cellTest2);
			Assert::IsTrue(cellTest2 == cellTest3);
		}

		TEST_METHOD(GetCellType)
		{
			Cell cell(true, true, CellType::Empty);
			Assert::IsTrue(cell.GetType() == CellType::Empty);
		}

		TEST_METHOD(SetCellType)
		{
			Cell cell(true, true, CellType::Number);
			cell.SetCellType(CellType::Bomb);
			Assert::IsTrue(cell.GetType() == CellType::Bomb);
		}
		
		TEST_METHOD(CellFlag)
		{
			Cell cell(true, false, CellType::Number);
			Assert::IsTrue(cell.IsFlag() == true);
		}

		TEST_METHOD(CellHidden)
		{
			Cell cell(true, false, CellType::Bomb);
			Assert::IsTrue(cell.isHidden() == false);
		}

		TEST_METHOD(CellSetHide)
		{
			Cell cell(true, true, CellType::Bomb);
			cell.SetCellHide();
			Assert::IsTrue(cell.isHidden() == false);
		}
		TEST_METHOD(CellDestructor)
		{
			Cell cell(true, false, CellType::Number);
			cell.~Cell();
			Assert::IsTrue(cell.GetType() == CellType::None);
		}

		TEST_METHOD(CellHeight)
		{
			Assert::IsTrue(Cell::GetHeight() == 30);
		}

		TEST_METHOD(SetCellFlag)
		{
			Cell cell(false, true, CellType::Bomb);
			cell.SetCellFlag();
			Assert::IsTrue(cell.IsFlag() == true);
			cell.SetCellFlag();
			Assert::IsTrue(cell.IsFlag() == false);
		}
	};
}
