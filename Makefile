all:
	c++ -std=c++14 src/script.cpp -Isrc/ -o prism

test_parser:
	c++ -std=c++14 src/testparser.cpp src/parlex.cpp -Isrc/ -o test_parser
