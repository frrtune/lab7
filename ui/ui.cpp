#include "../statistics/statistics.hpp"
#include "../streams/read_only_stream.hpp"
#include <pdcurses.h>
#include <string>

void open_ui() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    wbkgd(stdscr, COLOR_PAIR(1));
    
    std::string filename;
    Statistics<int> stats;
    bool data_loaded = false;
    
    while (true) {
        clear();
        
        attron(A_BOLD);
        mvprintw(0, 0, "Statistics");
        attroff(A_BOLD);
        
        mvprintw(2, 0, "Filename: ");
        echo();
        
        char input[256];
        getnstr(input, 255);
        filename = input;
        
        if (filename.empty()) {
            break;
        }
        
        try {
            ReadOnlyStream<int> stream(filename);
            stats.read_from_stream(stream);
            data_loaded = true;

            clear();
            mvprintw(0, 0, "Statistics");
            mvprintw(2, 0, "File loaded: %s", filename.c_str());
            mvprintw(4, 0, "Sum: %d", stats.sum());
            mvprintw(5, 0, "Min: %d", stats.min());
            mvprintw(6, 0, "Max: %d", stats.max());
            mvprintw(7, 0, "Median: %d", stats.get_median());
            mvprintw(9, 0, "Press any key to continue...");
            refresh();
            getch();
            
        } catch (const Error& e) {
            clear();
            mvprintw(0, 0, "Statistics");
            mvprintw(4, 0, "Error occured: %s", e.what());
            mvprintw(8, 0, "Press any key to continue");
            refresh();
            getch();
        }
    }
    endwin();
}