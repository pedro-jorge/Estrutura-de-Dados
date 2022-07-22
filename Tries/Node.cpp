#include <memory>
#include <list>

class Node {
private:
    std::unique_ptr<char> character;
    bool isEnd;
    std::list<std::shared_ptr<Node>> children;

    static auto createNode(char c, bool _isEnd) {
        return std::make_shared<Node>(std::make_unique<char>(c), _isEnd);
    }

public:
    explicit Node(std::unique_ptr<char> _character, bool _isEnd = false) {
        character = std::move(_character);
        isEnd = _isEnd;
    }

    explicit Node(char c, bool _isEnd = false) {
        character = std::make_unique<char>(c);
        isEnd = _isEnd;
    }

    [[nodiscard]] auto getCharacter() const noexcept{ return *character; }
    [[nodiscard]] bool isNull() const noexcept { return character == nullptr; }
    [[nodiscard]] bool isEndOfWord() const noexcept { return isEnd; }
    [[nodiscard]] int getChildrenSize() const noexcept { return (int)children.size(); }

    auto getUniqueChild() noexcept {
        return children.size() == 1 ? children.front() : std::make_shared<Node>(nullptr);
    }

    auto setAsEndOfWord() noexcept { isEnd = true; }


    auto hasChild(const char c) {
        for(const auto &child : children) {
            if(child->getCharacter() == c)
                return child;
        }

        return std::make_shared<Node>(nullptr);
    }

    auto addChild(const char c, bool _isEnd = false) {
        auto node = hasChild(c);

        if(node->isNull()) {
            node = createNode(c, _isEnd);
            children.push_back(node);
        }

        return node;
    }
};