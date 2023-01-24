#pragma once

#include <QWidget>
#include "ui_UserRegisterWindow.h"
#include <QDialog>
#include"head.h"
#include<Account.h>
#include <QInputDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QDialogButtonBox>
#include<QCombobox>
#include<qpushbutton.h>
#include<QMessagebox>
class UserRegisterWindow : public QWidget
{
	Q_OBJECT

public:
	UserRegisterWindow(QWidget *parent = Q_NULLPTR);
	~UserRegisterWindow();

private:
	Ui::UserRegisterWindow *ui;
	User *user;
public slots:
	void on_returnbotton_clicked();//ÍË³ö×¢²á
private slots:
	void confirm_clicked();//È·¶¨×¢²á
	void username_finished();
	void password_finished();
	void confirmPassword();
	void name_finished();
	void number_finished();
	void address_finished();
};
