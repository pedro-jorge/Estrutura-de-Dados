#include <iostream>
#include <fstream>
#include <vector>
#include "Node.cpp" // forward_list, memory

class Trie {
private:
    std::shared_ptr<Node> root;

public:
    Trie() {
        root = std::make_shared<Node>(nullptr);
    }

    auto addWord(const std::string& word) {
        auto node = root;
        for(const auto c : word) {
            node = node->addChild(c);
        }

        node->setAsEndOfWord();
    }

    auto hasWord(const std::string& word) {
        auto node = root;
        for(const auto c : word) {
            node = node->hasChild(c);
            if(node->isNull())
                return false;
        }

        return node->isEndOfWord();
    }

    auto findBestMatch(const std::string& word) {
        auto node = root;
        std::string s;

        for(const auto c : word) {
            node = node->hasChild(c);
            if(node->isNull())
                return s;
            s += node->getCharacter();
        }


        while(node->getChildrenSize() == 1 && !node->isNull()) {
            node = node->getUniqueChild();;
            s += node->getCharacter();
        }

        return s;
    }
};

int main() {

    Trie t;
    std::ifstream f("C:/Users/pjorg/Desktop/wordlist.txt");
    std::string line;
    std::vector<std::string> V;

    while(std::getline(f, line)) {
        t.addWord(line);
        V.push_back(line);
    }

    f.close();

    for(auto const &v : V)
        std::cout << t.hasWord(v);

    return 0;
}