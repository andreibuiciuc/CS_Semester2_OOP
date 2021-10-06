#pragma once

#include <QAbstractTableModel>
#include "../Controller/controllerUser.h"

class TutorialsTableModel: public QAbstractTableModel{
private:
    FileRepository repository;

public:
    explicit TutorialsTableModel(const FileRepository& repository, QObject* parent = nullptr);

    ~TutorialsTableModel() override;

    // The number of rows
    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

    // The number of columns
    int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

    // The value at a given position
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // Add header data
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Called when a cell is edited
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    // Set properties to a cell
    Qt::ItemFlags flags(const QModelIndex& index) const override;
};