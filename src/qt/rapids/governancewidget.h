// Copyright (c) 2021 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php.

#ifndef GOVERNANCEWIDGET_H
#define GOVERNANCEWIDGET_H

#include "qt/rapids/pwidget.h"
#include "qt/rapids/proposalcard.h"

#include <QGridLayout>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStyledItemDelegate>
#include <QApplication>

namespace Ui {
class governanceWidget;
}

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

class MNModel;
class RapidsGUI;
class GovernanceModel;
class TooltipMenu;

class Delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit Delegate(QObject *parent = nullptr) :
            QStyledItemDelegate(parent) {}

    void setValues(QList<QString> _values) {
        values = std::move(_values);
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        if (!index.isValid())
            return;

        QStyleOptionViewItem opt = option;
        QStyle *style = option.widget ? option.widget->style() : QApplication::style();
        opt.text = values.value(index.row());
        style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, option.widget);
    }

private:
    QList<QString> values;
};

class GovernanceWidget : public PWidget
{
    Q_OBJECT

public:
    explicit GovernanceWidget(RapidsGUI* parent);
    ~GovernanceWidget() override;

    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;
    void resizeEvent(QResizeEvent *event) override;
    void loadClientModel() override;
    void loadWalletModel() override;
    void setGovModel(GovernanceModel* _model);
    void setMNModel(MNModel* _mnModel);

public Q_SLOTS:
    void onFilterChanged(const QString& value);
    void chainHeightChanged(int height);
    void onVoteForPropClicked(const ProposalInfo& proposalInfo);
    void onCreatePropClicked();
    void onMenuClicked(ProposalCard* card);
    //
    void onCopyUrl();
    void onOpenClicked();
    void onMoreInfoClicked();

private:
    Ui::governanceWidget *ui;
    GovernanceModel* governanceModel{nullptr};
    MNModel* mnModel{nullptr};
    bool isSync{false};
    QGridLayout* gridLayout{nullptr}; // cards
    std::vector<ProposalCard*> cards;
    int propsPerRow = 0;
    QTimer* refreshTimer{nullptr};

    TooltipMenu* propMenu{nullptr};
    ProposalCard* menuCard{nullptr};

    // Proposals filter
    Optional<ProposalInfo::Status> statusFilter{nullopt};

    void showEmptyScreen(bool show);
    void tryGridRefresh(bool force=false);
    ProposalCard* newCard();
    void refreshCardsGrid(bool forceRefresh);
    int calculateColumnsPerRow();
};

#endif // GOVERNANCEWIDGET_H
