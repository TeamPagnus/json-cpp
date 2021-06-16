import unittest
import os
from subprocess import getstatusoutput

CPP_EXECUTABLE = "test.o"
CPP_FILENAME = "test.cpp"

CPP_TEMPLATE = """
#include "../src/json-cpp.h"

int main()
{
    json test = json::from_string("/*source*/");
    std::cout << test/*snipet*/ << std::endl;
    return 0;
}
"""

def createCpp(cppSnippet, source):
    escapedSource = source.replace('"', '\\"')

    f = open(CPP_FILENAME, "w")
    f.write(CPP_TEMPLATE.replace("/*snipet*/",cppSnippet).replace("/*source*/", escapedSource))
    f.close()

def compile():
    status, output = getstatusoutput(f"g++ {CPP_FILENAME} -o {CPP_EXECUTABLE}")
    if status != 0:
        raise Exception(f"compile error {status}:{os.linesep}{output}")

def run(cppSnippet,source):
    createCpp(cppSnippet,source)
    compile()
    status, output = getstatusoutput(f"./{CPP_EXECUTABLE}")
    if status == 0:
        return output
    raise Exception(f"run error {status}:{os.linesep}{output}")

class SimpleSnippetsCases(unittest.TestCase):

    def test_key_value(self):
        source = '{"key":"value"}'
        cppSnippet = '["key"]'
        expectedValue = 'value'
        self.assertEqual(expectedValue, run(cppSnippet,source))

    def test_happy_path(self):
        source = '{"test":"expectedValue"}'
        cppSnippet = '["test"]'
        expectedValue = 'expectedValue'
        self.assertEqual(expectedValue, run(cppSnippet,source))

    def test_happy_path(self):
        source = '{"test":"expectedValue"}'
        cppSnippet = '["test"]'
        expectedValue = 'expectedValue'
        self.assertEqual(expectedValue, run(cppSnippet,source))
    
    def tearDown(self) -> None:
        os.remove(CPP_EXECUTABLE)
        os.remove(CPP_FILENAME)
        return super().tearDown()

if __name__ == "__main__":
    unittest.main()
