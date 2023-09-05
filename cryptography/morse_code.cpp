// C++ 20 MSVC 通过编译
#include <iostream>
#include <array>
#include <vector>
#include <ranges>

struct morse_parser
{
private:
	const std::string space_{" "};
	using char_seq = std::vector<char>;
	char_seq clear_text_{
		[]
		{
			constexpr auto letters{std::views::iota('a') | std::views::take(26)};
			constexpr auto digits{std::views::iota('0') | std::views::take(10)};
			return std::array{letters, digits} | std::views::join | std::ranges::to<char_seq>();
		}()

	};
	using str_seq = std::array<std::string, 36>;
	str_seq morse_code_{
		".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
		".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---",
		"...--", "....-", ".....", "-....", "--...", "---..", "----."
	};

public:
	const std::string& operator[](const char& c) const noexcept
	{
		if (c == ' ')
		{
			return this->space_;
		}
		return morse_code_[c - 'a'];
	}

	const char& operator[](const std::string& s) const noexcept
	{
		const auto it{std::ranges::find(morse_code_.cbegin(), morse_code_.cend(), s)};
		const auto index{std::distance(morse_code_.cbegin(), it)};
		return clear_text_[index];
	}
};


int main()
{
	const morse_parser mp{};
	std::cout << "你是要加密（E）还是要解密（D）呢？输入其他字符退出。" << std::endl;
	while (true)
	{
		char option{};
		std::cin >> option;
		if (option == 'E')
		{
			std::cout << "请输入明文：" << std::endl;
			char letter{};
			std::cin.get(); //扔掉多余的换行符
			std::cin.get(letter);
			while (letter != '\n')
			{
				std::cout << mp[letter] << " ";
				std::cin.get(letter);
			}
			std::cout << std::endl;
		}
		else if (option == 'D')
		{
			std::cout << "请输入密文：" << std::endl;
			std::string morse_code{};
			std::cin >> morse_code;
			while (std::cin.peek() != '\0')
			{
				std::cout << mp[morse_code];
				std::cin >> morse_code;
			}
		}
		else
		{
			std::cout << "程序即将退出";
			break;
		}
	}
}

