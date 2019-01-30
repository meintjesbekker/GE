#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GEUnitTest
{	
	BEGIN_TEST_MODULE_ATTRIBUTE()
		TEST_MODULE_ATTRIBUTE(L"Date", L"2010/6/12")
	END_TEST_MODULE_ATTRIBUTE()

	TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		Logger::WriteMessage("In Module Initialize");
	}

	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		Logger::WriteMessage("In Module Cleanup");
	}

	TEST_CLASS(UnitTest1)
	{
	public:
		
		UnitTest1()
		{
			Logger::WriteMessage("In UnitTest1");
		}

		~UnitTest1()
		{
			Logger::WriteMessage("In ~UnitTest1");
		}

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In Class Initialize");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In Class Cleanup");
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(Method1)
			TEST_OWNER(L"OwnerName")
			TEST_PRIORITY(1)
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(Method1)
		{
			Logger::WriteMessage("In Method1");
			Assert::AreEqual(0, 0);
		}

		TEST_METHOD(Method2)
		{
			Assert::Fail(L"Fail");
		}

		TEST_METHOD(Method3)
		{
			std::string teststring = "My Unit Test";
			std::string classstring = "My Unit Test";
			Assert::AreEqual(teststring, classstring);
		}

		TEST_METHOD(Method4)
		{
			//CAverage AverageGenerator;
			//float average = AverageGenerator.GetAverage();
			//Assert::AreEqual(float(0.0), average);
		}

	};
}