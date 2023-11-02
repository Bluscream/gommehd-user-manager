﻿#include "userwidget.hpp"


UserWidget::UserWidget(sqlw* UserManager) : UserManager(UserManager), ui(new Ui::UserWidget) {
	initphase = true;

	ui->setupUi(this);
	log("userwidget setup complete");

	connect(this->findChild<QTableWidget*>("TW_BUDDY"), SIGNAL(cellClicked(int,int)),this, SLOT(buddyItemClicked(int, int)));
	connect(this->findChild<QTableWidget*>("TW_BLOCKED"), SIGNAL(cellClicked(int,int)), this, SLOT(blockedItemClicked(int, int)));
	connect(this->findChild<QTableWidget*>("TW_NAMES"), SIGNAL(cellClicked(int,int)), this, SLOT(blockedNameItemClicked(int, int)));
	connect(this->findChild<QTableWidget*>("TW_COUNTRY"), SIGNAL(cellClicked(int, int)), this, SLOT(blockedCountryItemClicked(int, int)));

	fillBuddyTable("");
	fillBlockedTable("");
	fillBlockedNameTable();
	fillBlockedCountryTable();
	initphase = false;
}


UserWidget::UserWidget(sqlw * UserManager, std::string UID, bool buddy) : UserManager(UserManager), ui(new Ui::UserWidget)
{

	initphase = true;

	ui->setupUi(this);
	log("userwidget setup complete");

	connect(this->findChild<QTableWidget*>("TW_BUDDY"), SIGNAL(cellClicked(int, int)), this, SLOT(buddyItemClicked(int, int)));
	connect(this->findChild<QTableWidget*>("TW_BLOCKED"), SIGNAL(cellClicked(int, int)), this, SLOT(blockedItemClicked(int, int)));
	connect(this->findChild<QTableWidget*>("TW_NAMES"), SIGNAL(cellClicked(int, int)), this, SLOT(blockedNameItemClicked(int, int)));
	connect(this->findChild<QTableWidget*>("TW_COUNTRY"), SIGNAL(cellClicked(int, int)), this, SLOT(blockedCountryItemClicked(int, int)));



	if (buddy) {
		this->findChild<QTabWidget*>("tabWidget")->setCurrentIndex(0);
		fillBuddyTable(UID);
		fillBlockedTable("");
	}
	else {
		this->findChild<QTabWidget*>("tabWidget")->setCurrentIndex(1);
		fillBuddyTable("");
		fillBlockedTable(UID);
	}
	fillBlockedNameTable();
	fillBlockedCountryTable();

	initphase = false;

}

UserWidget::~UserWidget() {}

void UserWidget::on_chk_BuddyAutoTalkpower_stateChanged(int state)
{
	if (initphase) return;
	log("on_chk_BuddyAutoTalkpower");
	if (currentItemBuddy == nullptr) return;
	BuddyUser buddyUser = UserManager->getBuddybyUID(currentItemBuddy->text().toStdString());
	buddyUser.AutoTalkpower = intToBool(state);
	UserManager->updateBuddy(buddyUser);
}

void UserWidget::on_chk_BuddyAntiChannelBan_stateChanged(int state)
{
	if (initphase) return;
	log("on_chk_BuddyAntiChannelBan");
	if (currentItemBuddy == nullptr) return;
	BuddyUser buddyUser = UserManager->getBuddybyUID(currentItemBuddy->text().toStdString());
	buddyUser.AntiChannelBan = intToBool(state);
	UserManager->updateBuddy(buddyUser);
}

void UserWidget::on_chk_BuddyAutoOperator_stateChanged(int state)
{
	if (initphase) return;
	log("on_chk_BuddyAutoOperator");
	if (currentItemBuddy == nullptr) return;
	BuddyUser buddyUser = UserManager->getBuddybyUID(currentItemBuddy->text().toStdString());
	buddyUser.AutoOperator = intToBool(state);
	UserManager->updateBuddy(buddyUser);
}

void UserWidget::on_chk_BlockedAutoBan_stateChanged(int state)
{
	if (initphase) return;
	log("on_chk_BlockedAutoBan");
	if (currentItemBlocked == nullptr) return;
	BlockedUser blockedUser = UserManager->getBlockedbyUID(currentItemBlocked->text().toStdString());
	blockedUser.AutoBan = intToBool(state);
	UserManager->updateBlocked(blockedUser);
}

void UserWidget::on_chk_BlockedAutoKick_stateChanged(int state)
{
	if (initphase) return;
	log("on_chk_BlockedAutoKick");
	if (currentItemBlocked == nullptr) return;
	BlockedUser blockedUser = UserManager->getBlockedbyUID(currentItemBlocked->text().toStdString());
	blockedUser.AutoKick = intToBool(state);
	UserManager->updateBlocked(blockedUser);
}

void UserWidget::on_chk_BlockedNameAutoBan_stateChanged(int state)
{
	if (initphase) return;
	log("on_chk_BlockedNameAutoBan");
	if (currentItemName == nullptr) return;
	BlockedName blockedName = UserManager->getBlockedNamebyNAME(currentItemName->text().toStdString());
	blockedName.AutoBan = intToBool(state);
	UserManager->updateName(blockedName);
}

void UserWidget::on_chk_BlockedNameAutoKick_stateChanged(int state)
{
	if (initphase) return;
	log("on_chk_BlockedNameAutoKick");
	if (currentItemName == nullptr) return;
	BlockedName blockedName = UserManager->getBlockedNamebyNAME(currentItemName->text().toStdString());
	blockedName.AutoKick = intToBool(state);
	UserManager->updateName(blockedName);
}

void UserWidget::on_btn_buddynamesave_clicked()
{
	if (currentItemBuddy == nullptr) return;
	BuddyUser buddyUser = UserManager->getBuddybyUID(currentItemBuddy->text().toStdString());
	buddyUser.SavedName = this->findChild<QLineEdit*>("textbox_buddyname")->text();
	UserManager->updateBuddy(buddyUser);
}

void UserWidget::on_btn_blocknamesave_clicked()
{
	if (currentItemBlocked == nullptr) return;
	BlockedUser blockedUser = UserManager->getBlockedbyUID(currentItemBlocked->text().toStdString());
	blockedUser.SavedName = this->findChild<QLineEdit*>("textbox_blockname")->text();
	UserManager->updateBlocked(blockedUser);
}

void UserWidget::on_btn_blocknameNamesave_clicked()
{
	if (currentItemName == nullptr) return;
	BlockedName blockedName = UserManager->getBlockedNamebyNAME(currentItemName->text().toStdString());
	blockedName.Name = this->findChild<QLineEdit*>("textbox_blockedname")->text();
	UserManager->updateName(blockedName);
}

void UserWidget::on_chk_BlockedCountryAutoBan_stateChanged(int state)
{
	if (initphase) return;
	log("chk_BlockedCountryAutoBan");
	if (currentItemCountry == nullptr) return;
	BlockedCountry blockedCountry = UserManager->getBlockedCountrybyCountryTag(currentItemCountry->text().toStdString());
	blockedCountry.AutoBan = intToBool(state);
	UserManager->UpdateCountry(blockedCountry);
}

void UserWidget::on_chk_BlockedCountryAutoKick_stateChanged(int state)
{
	if (initphase) return;
	log("chk_BlockedCountryAutoKick");
	if (currentItemCountry == nullptr) return;
	BlockedCountry blockedCountry = UserManager->getBlockedCountrybyCountryTag(currentItemCountry->text().toStdString());
	blockedCountry.AutoKick = intToBool(state);
	UserManager->UpdateCountry(blockedCountry);
}

void UserWidget::on_btn_buddyRemove_clicked()
{
	if (currentItemBuddy == nullptr) return;
	BuddyUser buddyUser = UserManager->getBuddybyUID(currentItemBuddy->text().toStdString());
	UserManager->removeBuddyList(buddyUser);
	this->findChild<QTableWidget*>("TW_BUDDY")->removeRow(currentItemBuddy->row());
	currentItemBuddy = nullptr;
	this->findChild<QCheckBox*>("chk_BuddyAutoOperator")->setChecked(false);
	this->findChild<QCheckBox*>("chk_BuddyAutoTalkpower")->setChecked(false);
	this->findChild<QCheckBox*>("chk_BuddyAntiChannelBan")->setChecked(false);
	this->findChild<QLineEdit*>("textbox_buddyname")->setText("");
}

void UserWidget::on_btn_blockedRemove_clicked()
{
	if (currentItemBlocked == nullptr) return;
	BlockedUser blockedUser = UserManager->getBlockedbyUID(currentItemBlocked->text().toStdString());
	UserManager->removeBlockedList(blockedUser);
	this->findChild<QTableWidget*>("TW_BLOCKED")->removeRow(currentItemBlocked->row());
	currentItemBlocked = nullptr;
	this->findChild<QCheckBox*>("chk_BlockedAutoBan")->setChecked(false);
	this->findChild<QCheckBox*>("chk_BlockedAutoKick")->setChecked(false);
	this->findChild<QLineEdit*>("textbox_blockname")->setText("");
}

void UserWidget::on_btn_NameRemove_clicked()
{
	if (currentItemName == nullptr) return;
	BlockedName blockedName = UserManager->getBlockedNamebyNAME(currentItemName->text().toStdString());
	UserManager->removeNameList(blockedName);
	this->findChild<QTableWidget*>("TW_NAMES")->removeRow(currentItemName->row());
	currentItemName = nullptr;
	this->findChild<QCheckBox*>("chk_BlockedNameAutoBan")->setChecked(false);
	this->findChild<QCheckBox*>("chk_BlockedNameAutoKick")->setChecked(false);
	this->findChild<QLineEdit*>("textbox_blockedname")->setText("");
}

void UserWidget::on_btn_countryRemove_clicked()
{
	if (currentItemCountry == nullptr) return;
	BlockedCountry blockedCountry = UserManager->getBlockedCountrybyCountryTag(currentItemCountry->text().toStdString());
	UserManager->removeCountryList(blockedCountry);
	this->findChild<QTableWidget*>("TW_COUNTRY")->removeRow(currentItemCountry->row());	
	currentItemCountry = nullptr;
	this->findChild<QCheckBox*>("chk_BlockedCountryAutoBan")->setChecked(false);
	this->findChild<QCheckBox*>("chk_BlockedCountryAutoKick")->setChecked(false);
}


void UserWidget::buddyItemClicked(int row,int column)
{
	log("buddyItemClicked");
	initphase = true;
	currentItemBuddy = this->findChild<QTableWidget*>("TW_BUDDY")->item(row, 1);

	BuddyUser buddyUser = UserManager->getBuddybyUID(currentItemBuddy->text().toStdString());
	if (buddyUser.dummy_Return) {
	this->findChild<QCheckBox*>("chk_BuddyAutoOperator")->setChecked(buddyUser.AutoOperator);
	this->findChild<QCheckBox*>("chk_BuddyAutoTalkpower")->setChecked(buddyUser.AutoTalkpower);
	this->findChild<QCheckBox*>("chk_BuddyAntiChannelBan")->setChecked(buddyUser.AntiChannelBan);
	this->findChild<QLineEdit*>("textbox_buddyname")->setText(buddyUser.SavedName);
	}
	else {
		log("Error: BuddyUser in list not found");
	}
	initphase = false;
}

void UserWidget::blockedItemClicked(int row, int column)
{
	log("blockedItemClicked");
	initphase = true;

	currentItemBlocked = this->findChild<QTableWidget*>("TW_BLOCKED")->item(row, 1);
	
	BlockedUser blockedUser = UserManager->getBlockedbyUID(currentItemBlocked->text().toStdString());
	if (blockedUser.dummy_Return) {
	this->findChild<QCheckBox*>("chk_BlockedAutoBan")->setChecked(blockedUser.AutoBan);
	this->findChild<QCheckBox*>("chk_BlockedAutoKick")->setChecked(blockedUser.AutoKick);
	this->findChild<QLineEdit*>("textbox_blockname")->setText(blockedUser.SavedName);
	}
	else {
		log("Error: BlockedUser in list not found");
	}
	initphase = false;
}

void UserWidget::blockedNameItemClicked(int row, int column)
{
	log("blockedNameItemClicked");
	initphase = true;
	currentItemName = this->findChild<QTableWidget*>("TW_NAMES")->item(row, 0);
	BlockedName blockedname = UserManager->getBlockedNamebyNAME(currentItemName->text().toStdString());
	if (blockedname.dummy_Return) {
		this->findChild<QCheckBox*>("chk_BlockedNameAutoBan")->setChecked(blockedname.AutoBan);
		this->findChild<QCheckBox*>("chk_BlockedNameAutoKick")->setChecked(blockedname.AutoKick);
		this->findChild<QLineEdit*>("textbox_blockedname")->setText(blockedname.Name);
	}
	else {
		log("Error: Name in list not found");
	}
	initphase = false;
}

void UserWidget::blockedCountryItemClicked(int row, int column)
{
	log("blockedCountryItemClicked");
	initphase = true;
	currentItemCountry = this->findChild<QTableWidget*>("TW_COUNTRY")->item(row, 0);
	BlockedCountry blockedcountry = UserManager->getBlockedCountrybyCountryTag(currentItemCountry->text().toStdString());
	if (blockedcountry.dummy_Return) {
		this->findChild<QCheckBox*>("chk_BlockedCountryAutoBan")->setChecked(blockedcountry.AutoBan);
		this->findChild<QCheckBox*>("chk_BlockedCountryAutoKick")->setChecked(blockedcountry.AutoKick);
	}
	else {
		log("Error: Country in list not found");
	}
	initphase = false;
}

void UserWidget::fillBuddyTable(std::string UID)
{
	size_t rowCount = UserManager->buddyList.size();
	bool found = false;
	this->findChild<QTableWidget*>("TW_BUDDY")->setRowCount((int)rowCount);
	int row = 0;
	for (auto it = UserManager->buddyList.begin(); it != UserManager->buddyList.end(); it++) {
		this->findChild<QTableWidget*>("TW_BUDDY")->setItem(row, 0, new QTableWidgetItem(it->SavedName));
		QTableWidgetItem* newItem = new  QTableWidgetItem(it->UID);
		this->findChild<QTableWidget*>("TW_BUDDY")->setItem(row, 1, newItem);
		if (UID == it->UID.toStdString()) {
			newItem->setSelected(true);
			//this->findChild<QTableWidget*>("TW_BUDDY")->setItemSelected(newItem, true);
			buddyItemClicked(row, 1);
			currentItemBuddy = this->findChild<QTableWidget*>("TW_BUDDY")->item(row, 1);
			found = true;
		}
		row++;
	}
	
}

void UserWidget::fillBlockedTable(std::string UID = "")
{
	size_t rowCount = UserManager->blockList.size();
	bool found = false;
	this->findChild<QTableWidget*>("TW_BLOCKED")->setRowCount((int)rowCount);
	int row = 0;
	for (auto it = UserManager->blockList.begin(); it != UserManager->blockList.end(); it++) {
		this->findChild<QTableWidget*>("TW_BLOCKED")->setItem(row, 0, new QTableWidgetItem(it->SavedName));
		QTableWidgetItem* newItem = new  QTableWidgetItem(it->UID);
		this->findChild<QTableWidget*>("TW_BLOCKED")->setItem(row, 1, newItem);
		if (UID == it->UID.toStdString()) {
			//this->findChild<QTableWidget*>("TW_BLOCKED")->setItemSelected(newItem, true);
			newItem->setSelected(true);
			blockedItemClicked(row, 1);
			currentItemBlocked = this->findChild<QTableWidget*>("TW_BLOCKED")->item(row, 1);
			found = true;
		}
		row++;
	}
	
}

void UserWidget::fillBlockedNameTable()
{
	size_t rowCount = UserManager->nameBlockList.size();
	this->findChild<QTableWidget*>("TW_NAMES")->setRowCount((int)rowCount);
	int row = 0;
	for (auto it = UserManager->nameBlockList.begin(); it != UserManager->nameBlockList.end(); it++) {
		this->findChild<QTableWidget*>("TW_NAMES")->setItem(row, 0, new QTableWidgetItem(it->Name));
		row++;
	}
	
	
}

void UserWidget::fillBlockedCountryTable()
{
	size_t rowCount = UserManager->countryList.size();
	this->findChild<QTableWidget*>("TW_COUNTRY")->setRowCount((int)rowCount);
	int row = 0;
	for (auto it = UserManager->countryList.begin(); it != UserManager->countryList.end(); it++) {
		this->findChild<QTableWidget*>("TW_COUNTRY")->setItem(row, 0, new QTableWidgetItem(it->CountryTag));
		row++;
	}
}

