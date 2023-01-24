#pragma once

#include <QWidget>
#include "ui_CourierRegisterWindow.h"
#include <QDialog>
#include <head.h>
#include<Account.h>
#include <QInputDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QDialogButtonBox>
#include<QCombobox>
#include<qpushbutton.h>
#include<QMessagebox>
class CourierRegisterWindow : public QWidget
{
	Q_OBJECT

public:
	CourierRegisterWindow(QWidget *parent = Q_NULLPTR);
	~CourierRegisterWindow();

private:
	Ui::CourierRegisterWindow *ui;
	Courier* courier;
public slots:
	void on_returnbotton_clicked();//ÍË³ö×¢²á
private slots:
	void confirm_clicked();//È·¶¨×¢²á
	void username_finished();
	void password_finished();
	void confirmPassword();
	void name_finished();
	void number_finished();
};
