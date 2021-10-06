
#include <QFont>
#include "TutorialsTableModel.h"

TutorialsTableModel::TutorialsTableModel(const FileRepository& repository, QObject* parent): QAbstractTableModel{parent} {
    this->repository = repository;
}

TutorialsTableModel::~TutorialsTableModel()  = default;

int TutorialsTableModel::rowCount(const QModelIndex &parent) const {
    int count = this->repository.getLength();
    return count + 1;
}

int TutorialsTableModel::columnCount(const QModelIndex &parent) const {
    return 6;
}

QVariant TutorialsTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();

    std::vector<Tutorial> tutorials = this->repository.getData();
    if(row == tutorials.size()) {
        return QVariant();
    }

    Tutorial tutorial = tutorials[row];

    if(role == Qt::DisplayRole || role == Qt::EditRole) {
        switch(column)
        {
            case 0:
                return QString::fromStdString(tutorial.getTitle());
            case 1:
                return QString::fromStdString(tutorial.getPresenter());
            case 2:
                return QString::number(tutorial.getDuration().first);
            case 3:
                return QString::number(tutorial.getDuration().second);
            case 4:
                return QString::number(tutorial.getLikes());
            case 5:
                return QString::fromStdString(tutorial.getLink());
            default:
                break;
        }
    }

    if(role == Qt::FontRole) {
        QFont font("Times", 8, 10, true);
        return font;
    }

    return QVariant{};
}

QVariant TutorialsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal) {
            switch(section)
            {
                case 0:
                    return QString{"Title"};
                case 1:
                    return QString{"Presenter"};
                case 2:
                    return QString{"Minutes"};
                case 3:
                    return QString{"Seconds"};
                case 4:
                    return QString{"Likes"};
                case 5:
                    return QString{"Link"};
                default:
                    break;
            }
        }
    }

    if(role == Qt::FontRole) {
        QFont font("Times", 8, 10);
        font.setBold(true);
        return font;
    }

    return QVariant{};
}

bool TutorialsTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid() || role != Qt::EditRole) {
        return false;
    }

    int tutorialIndex = index.row();
    std::vector<Tutorial> tutorials = this->repository.getData();
    int minutes, seconds;

    Tutorial& currentTutorial = tutorials[tutorialIndex];
    switch (index.column()) {
        case 0:
            currentTutorial.setTitle(value.toString().toStdString());
            break;
        case 1:
            currentTutorial.setPresenter(value.toString().toStdString());
            break;
        case 2:
            minutes = value.toInt();
        case 3:
            seconds = value.toInt();
            currentTutorial.setDuration(std::pair<int, int>(minutes,seconds));
            break;
        case 4:
            currentTutorial.setLikes(value.toInt());
            break;
        case 5:
            currentTutorial.setLink(value.toString().toStdString());
    }
    this->repository.updateElement(tutorialIndex, currentTutorial.getLikes());

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags TutorialsTableModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}