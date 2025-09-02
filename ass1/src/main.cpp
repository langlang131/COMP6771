#include "word_break.h"

#include <iostream>

// Please note: it's not good practice to test your code via a main function that does
//  printing. Instead, you should be using your test folder. This file should only really
//  be used for more "primitive" debugging as we know that working solely with test
//  frameworks might be overwhelming for some.

auto main() -> int {
    auto const english_lexicon = word_break::read_lexicon("./english.txt");
    auto const sentences = word_break::word_break("dogsandragonflytobeornotobethatisthequestionstudentsstudyprogrammingtodaydogsandragonflytobeornotobethatisthequestionstudentsstudyprogrammingtodaybirdssingbeautifulmelodiescatandogruntimeandtimeagainseethesunrisethereisnoplacehomewhatimeisitanicedaynotevenonceletmegooutinthenameofgodgoingtowashingtonseaandlandhotandcoldbirdssingbeautifulmelodiescatandogruntimeandtimeagainseethesunrisethereisnoplacehomewhatimeisitanicedaynotevenonceletmegooutinthenameofgodgoingtowashingtonseaandlandhotandcold", english_lexicon);
    // debug here
    std::cout << "Found " << sentences.size() << " result(s).\n";

    if (!sentences.empty()) {
        std::cout << "Each sentence uses " << sentences[0].size() << " words (minimum).\n\n";
    }
    
    for (size_t i = 0; i < std::min(size_t(2), sentences.size()); ++i) {
        std::cout << i + 1 << ". ";
        for (const auto& word : sentences[i]) {
            std::cout << word << " ";
        }
        std::cout << '\n';
    }
    return 0;    
}
