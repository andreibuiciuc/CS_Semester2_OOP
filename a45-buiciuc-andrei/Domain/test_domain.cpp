#include "test_domain.h"
#include <assert.h>
#include "utility"
#include "tutorial.h"

void test_tutorial(){
    std::pair<int, int>duration(20, 30);
    Tutorial tutorial("Andrei", "Bui", duration, 1000, "https://www.somewhere.com");

    assert(tutorial.get_title() == "Andrei");
    assert(tutorial.get_presenter() == "Bui");
    assert(tutorial.get_duration() == duration);
    assert(tutorial.get_likes() == 1000);
    assert(tutorial.get_link() == "https://www.somewhere.com");
    tutorial.set_likes(2000);
    assert(tutorial.get_likes() == 2000);

    std::string tutorialStr = tutorial.str();
    assert(tutorialStr == "Andrei | Bui | 20:30 | 2000 | https://www.somewhere.com");
}