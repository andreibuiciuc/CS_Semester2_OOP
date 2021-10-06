#pragma once
#include <vector>
#include <tutorial.h>
#include <windows.h>

class AbstractWatchlist {
protected:
    std::vector<Tutorial> data;
public:
     AbstractWatchlist();

    virtual ~AbstractWatchlist();

    virtual void open() = 0;

    virtual void write() = 0;

    void setData(const std::vector<Tutorial>& data);

    void process(const std::vector<Tutorial>& data);
};


class CSVWatchlist: public AbstractWatchlist {
private:
    std::string filename;

public:
    explicit CSVWatchlist(const std::string& filename);

    ~CSVWatchlist() override;

    /// Opens the CSV in Notepad
    void open() override;

    void write() override;

};


class HTMLWatchlist: public AbstractWatchlist {
private:
    std::string filename;

public:
    explicit HTMLWatchlist(const std::string& filename);

    ~HTMLWatchlist() override;

    /// Opens the HTML in browser
    void open() override;

    void write() override;
};



