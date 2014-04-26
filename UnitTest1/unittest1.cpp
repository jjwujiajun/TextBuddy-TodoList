#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(sortingTest)
	{
	public:
		
		TEST_METHOD(alphabetTest) {
			TextFile textFile;
			textFile.addNew("c");
			textFile.addNew("a");
			textFile.addNew("b");

			vector<string> testVector;
			testVector.push_back("a");
			testVector.push_back("b");
			testVector.push_back("c");

			textFile.sortRowsAlphabetically();

			Assert::AreEqual(textFile.getTexts().at(0), testVector.at(0));
			Assert::AreEqual(textFile.getTexts().at(1), testVector.at(1));
			Assert::AreEqual(textFile.getTexts().at(2), testVector.at(2));
		}

		TEST_METHOD(alphaumericTest) {
			TextFile textFile;
			textFile.addNew("29th");
			textFile.addNew("October");
			textFile.addNew("1991");

			vector<string> testVector;
			testVector.push_back("1991");
			testVector.push_back("29th");
			testVector.push_back("October");

			textFile.sortRowsAlphabetically();

			Assert::AreEqual(textFile.getTexts().at(0), testVector.at(0));
			Assert::AreEqual(textFile.getTexts().at(1), testVector.at(1));
			Assert::AreEqual(textFile.getTexts().at(2), testVector.at(2));
		}
	};

	TEST_CLASS(searchingTest)
	{
	public:

		TEST_METHOD(stringIdentificationTest) {
			TextFile textFile;
			
			vector<string> texts;
			texts.push_back("The fox jumps");
			texts.push_back("over the fence");
			texts.push_back("and fell down.");
			texts.push_back("So we all laughed at it.");
			texts.push_back("the fence is red btw.");
			
			string testInput = "the fence";
			
			vector<int> positiveSearch;
			positiveSearch.push_back(false);
			positiveSearch.push_back(true);
			positiveSearch.push_back(false);
			positiveSearch.push_back(false);
			positiveSearch.push_back(true);
			
			for (int i = 0; i < 5; ++i) {
				Assert::AreEqual(textFile.textDoesContainInput(texts[i], testInput), (bool)positiveSearch.at(i));
			}
		}

		TEST_METHOD(stringIndexingTest) {
			TextFile textFile;

			textFile.addNew("The fox jumps");
			textFile.addNew("over the fence");
			textFile.addNew("and fell down.");
			textFile.addNew("So we all laughed at it.");
			textFile.addNew("the fence is red btw.");

			string testInput = "the fence";
			textFile.searchFor(testInput);

			vector<string> expected;
			expected.push_back("2. over the fence");
			expected.push_back("5. the fence is red btw.");

			for (int i = 0; i < 2; ++i) {
				Assert::AreEqual(textFile.getPositiveSearch().at(i), expected.at(i));
			}

			testInput = "over";
			textFile.searchFor(testInput);

			vector<string> expected2;
			expected2.push_back("2. over the fence");

			Assert::AreEqual(textFile.getPositiveSearch().at(0), expected2.at(0));
		}
	};
}