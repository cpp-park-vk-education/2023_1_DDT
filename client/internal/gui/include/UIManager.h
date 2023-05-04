#ifndef INCLUDE_UIMANAGER_H_
#define INCLUDE_UIMANAGER_H_

#include "EntryWindow.h"
#include "UserWindow.h"

class UIManager {
public:
    UIManager();

    ~UIManager() = default;

    void showEntryWindow();
    void showUserWindow();

private:
    EntryWindow entryWindow;
    UserWindow userWindow;
};

#endif  // INCLUDE_UIMANAGER_H_
