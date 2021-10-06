//#include "test_domain.h"
//#include <assert.h>
//#include "utility"
//#include "tutorial.h"
//
//void test_tutorial(){
//    std::pair<int, int>duration(20, 30);
//    Tutorial tutorial("Andrei", "Bui", duration, 1000, "https://www.somewhere.com");
//
//    assert(tutorial.getTitle() == "Andrei");
//    assert(tutorial.getPresenter() == "Bui");
//    assert(tutorial.getDuration() == duration);
//    assert(tutorial.getLikes() == 1000);
//    assert(tutorial.getLink() == "https://www.somewhere.com");
//    tutorial.setLikes(2000);
//    assert(tutorial.getLikes() == 2000);
//
//    std::string tutorialStr = tutorial.str();
//    assert(tutorialStr == "Andrei | Bui | 20:30 | 2000 | https://www.somewhere.com");
//}