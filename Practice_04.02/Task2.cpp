#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string toLower(std::string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

bool isLetter(char c)
{
    return isalpha(c);
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::ifstream forbiddenFile("forbidden.txt");
    std::ofstream reportFile("report.txt");

    if (!inputFile.is_open() || !forbiddenFile.is_open())
    {
        std::cout << "Error opening files\n";
        return 1;
    }

    std::vector<std::string> forbiddenWords;
    std::string word;

    while (std::getline(forbiddenFile, word))
    {
        forbiddenWords.push_back(toLower(word));
    }

    std::string line;
    int num = 0;
    int total = 0;

    while (std::getline(inputFile, line))
    {
        num++;

        std::string lowerLine = toLower(line);

        for (int i = 0; i < forbiddenWords.size(); i++)
        {
            std::string forbidden = forbiddenWords[i];

            size_t position = lowerLine.find(forbidden);

            while (position != std::string::npos)
            {
                bool left = (position == 0) || !isLetter(lowerLine[position - 1]);
                bool right = (position + forbidden.size() >= lowerLine.size()) || !isLetter(lowerLine[position + forbidden.size()]);

                if (left && right)
                {
                    total++;
                    reportFile << "Line: " << num << "\nPosition: " << position + 1 << "\nWord: " << forbidden << "\nContext: " << line << "\n\n";
                }

                position = lowerLine.find(forbidden, position + 1);
            }
        }
    }

    reportFile << "Total: " << total << "\n";
    std::cout << "Matches: " << total << "\n";

    return 0;
}