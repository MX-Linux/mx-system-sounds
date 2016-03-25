/**********************************************************************
 *  mxsystemsounds.cpp
 **********************************************************************
 * Copyright (C) 2016 MX Authors
 *
 * Authors: Adrian
 *          MX & MEPIS Community <http://forum.mepiscommunity.org>
 *
 * This file is part of mx-system-sounds.
 *
 * mx-system-sounds is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * mx-system-sounds is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with mx-system-sounds.  If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************/


#include "mxsystemsounds.h"
#include "ui_mxsystemsounds.h"

#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFileDialog>

mxsystemsounds::mxsystemsounds(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mxsystemsounds)
{
    ui->setupUi(this);
    setup();
}

mxsystemsounds::~mxsystemsounds()
{
    delete ui;
}

// util function for getting bash command output and error code
Output mxsystemsounds::runCmd(QString cmd)
{
    QProcess *proc = new QProcess();
    QEventLoop loop;
    proc->setReadChannelMode(QProcess::MergedChannels);
    proc->start("/bin/bash", QStringList() << "-c" << cmd);
    proc->waitForFinished();
    Output out = {proc->exitCode(), proc->readAll().trimmed()};
    delete proc;
    return out;
}


// setup versious items first time program runs
void mxsystemsounds::setup()
{
    version = getVersion("mx-system-sounds");
    this->setWindowTitle(tr("MX System Sounds"));
    this->adjustSize();

    //intialize variables
    QString home_path = QDir::homePath();
    QString soundtheme = (runCmd("xfconf-query -c xsettings -p /Net/SoundThemeName").str);
    QString defaultloginsound = (runCmd("find  /usr/share/sounds/" + soundtheme + "/ |grep desktop-login").str);
    QString defaultlogoutsound = (runCmd("find  /usr/share/sounds/" + soundtheme + "/ |grep desktop-logout").str);
    QString currentlogin;
    QString currentlogout;
    QFileInfo file_info(home_path + "/.config/mx-sounds/startupsound.conf");
    if (file_info.exists()) {
        QString currentlogin = (runCmd("cat " + home_path + "/.config/mx-sounds/startupsound.conf").str);
        QFileInfo file_info(currentlogin);
        ui->pushButton_customloginsound->setText(file_info.baseName());
        ui->pushButton_customloginsound->setToolTip(file_info.filePath());
    } else {
        QFileInfo file_info(defaultloginsound);
        ui->pushButton_customloginsound->setText(file_info.baseName());
        ui->pushButton_customloginsound->setToolTip(file_info.filePath());
        currentlogin = defaultloginsound;
    }
    qDebug() << " default login is ";
    qDebug() << defaultloginsound;
    qDebug() << " current login is ";
    qDebug() << currentlogin;

    QFileInfo file_info2(home_path + "/.config/mx-sounds/logoutsound.conf");
    if (file_info2.exists()) {
        QString currentlogout = (runCmd("cat " + home_path + "/.config/mx-sounds/logoutsound.conf").str);
        QFileInfo file_info2(currentlogout);
        ui->pushButton_3_displaylogoutsound->setText(file_info2.baseName());
        ui->pushButton_3_displaylogoutsound->setToolTip(file_info2.filePath());
    } else {
        QFileInfo file_info2(defaultlogoutsound);
        ui->pushButton_3_displaylogoutsound->setText(file_info2.baseName());
        ui->pushButton_3_displaylogoutsound->setToolTip(file_info2.filePath());
        currentlogout = defaultlogoutsound;
    }
    qDebug() << " default logout is ";
    qDebug() << defaultlogoutsound;
    qDebug() << " current logout is ";
    qDebug() << currentlogout;

    //initial event sound setting
    if (runCmd("xfconf-query -c xsettings -p /Net/EnableEventSounds").str == "false") {
        ui->checkbox_eventsounds->setChecked(false);
    } else {
        ui->checkbox_eventsounds->setChecked(true);
    }

    //initial input feedback sound setting
    if (runCmd("xfconf-query -c xsettings -p /Net/EnableInputFeedbackSounds").str == "false") {
        ui->checkbox_inputsounds->setChecked(false);
    } else {
        ui->checkbox_inputsounds->setChecked(true);
    }

    //initial login sound setting
    if (runCmd("grep startup " + home_path + "/.config/mx-sounds/mx-login-logout_sounds.conf |cut -d '=' -f2").str == "false") {
        ui->checkbox_login->setChecked(false);
    } else {
        ui->checkbox_login->setChecked(true);
    }

    //initial logout setting
    if (runCmd("grep logout  " + home_path + "/.config/mx-sounds/mx-login-logout_sounds.conf |cut -d '=' -f2").str == "false") {
        ui->checkbox_logout->setChecked(false);
    } else {
        ui->checkbox_logout->setChecked(true);
    }

    //inital sound theme dialog setting
    ui->comboBox_theme->clear();
    QStringList theme_list;
    QStringList filter("index.theme");
    QDirIterator it("/usr/share/sounds", filter, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFileInfo file_info(it.next());
        QDir dir = file_info.absoluteDir();
        theme_list << dir.dirName();
    }
    ui->comboBox_theme->addItems(theme_list);
    ui->comboBox_theme->setCurrentText(soundtheme);
}


// Get version of the program
QString mxsystemsounds::getVersion(QString name)
{
    QString cmdstr = QString("dpkg -l %1 | awk 'NR==6 {print $3}'").arg(name);
    return runCmd(cmdstr).str;
}


//// slots ////


// Apply button clicked
void mxsystemsounds::on_buttonApply_clicked()
{
    QString home_path = QDir::homePath();

    // Event Sounds Enable or Disable
    if (ui->checkbox_eventsounds->isChecked()) {
        system("xfconf-query -c xsettings -p /Net/EnableEventSounds -s true");
    } else {
        system("xfconf-query -c xsettings -p /Net/EnableEventSounds -s false");
        ui->checkbox_inputsounds->setChecked(false);
    }

    // Input feedback Sounds Enable or Disable
    if (ui->checkbox_inputsounds->isChecked()){
        if (ui->checkbox_eventsounds->isChecked()){
            system("xfconf-query -c xsettings -p /Net/EnableInputFeedbackSounds -s true");
        } else {
            system("xfconf-query -c xsettings -p /Net/EnableInputFeedbackSounds -s false");
        }
    } else {
        system("xfconf-query -c xsettings -p /Net/EnableInputFeedbackSounds -s false");
    }

    // Login Sound Enable/disable
    if (ui->checkbox_login->isChecked()) {
        runCmd("sed -i -r s/startup=.*/startup=true/ " + home_path + "/.config/mx-sounds/mx-login-logout_sounds.conf");
    } else {
        runCmd("sed -i -r s/startup=.*/startup=false/ " + home_path + "/.config/mx-sounds/mx-login-logout_sounds.conf");
    }

    // Logout Sound Enable/disable
    if (ui->checkbox_logout->isChecked()) {
        runCmd("sed -i -r s/logout=.*/logout=true/  " + home_path + "/.config/mx-sounds/mx-login-logout_sounds.conf");
    } else {
        runCmd("sed -i -r s/logout=.*/logout=false/  " + home_path + "/.config/mx-sounds/mx-login-logout_sounds.conf");
    }

    // Set Sound Theme
    QString soundtheme2 = QString(ui->comboBox_theme->currentText());
    runCmd("xfconf-query -c xsettings -p /Net/SoundThemeName -s " + soundtheme2);


    // Set custom login sound

    QString defaultloginsound = (runCmd("find  /usr/share/sounds/" + soundtheme2 + "/ |grep desktop-login").str);
    QString currentloginsound = QString(ui->pushButton_customloginsound->toolTip());
    if (currentloginsound != defaultloginsound) {
        runCmd("echo " + currentloginsound +">" + home_path + "/.config/mx-sounds/startupsound.conf");
    } else {
        runCmd("rm -f " +home_path + "/.config/mx-sounds/startupsound.conf");
    }


    // Set custom logout sound
    QString defaultlogoutsound = (runCmd("find  /usr/share/sounds/" + soundtheme2 + "/ |grep desktop-logout").str);
    QString currentlogoutsound = QString(ui->pushButton_3_displaylogoutsound->toolTip());
    if (currentlogoutsound != defaultlogoutsound) {
        runCmd("echo " + currentlogoutsound +">" + home_path + "/.config/mx-sounds/logoutsound.conf");
    } else {
        runCmd("rm -f " +home_path + "/.config/mx-sounds/logoutsound.conf");
    }
    //reset defaults

    //reset theme
    if (ui->checkbox_reset_theme->isChecked()) {
        runCmd("xfconf-query -c xsettings -p /Net/SoundThemeName -s Borealis");
        ui->comboBox_theme->setCurrentText("Borealis");
    }

    //reset login sound
    if (ui->checkbox_reset_login->isChecked()) {
        runCmd("rm -f " + home_path + "/.config/mx-sounds/startupsound.conf");
    }

    //reset logout sound
    if (ui->checkbox_reset_logout->isChecked()) {
        runCmd("rm -f " + home_path + "/.config/mx-sounds/logoutsound.conf");
    }

    //reset checkboxes
    ui->checkbox_reset_theme->setChecked(false);
    ui->checkbox_reset_login->setChecked(false);
    ui->checkbox_reset_logout->setChecked(false);
}


// About button clicked
void mxsystemsounds::on_buttonAbout_clicked()
{
    this->hide();
    QMessageBox msgBox(QMessageBox::NoIcon,
                       tr("About MX System Sounds"), "<p align=\"center\"><b><h2>" +
                       tr("MX System Sounds") + "</h2></b></p><p align=\"center\">" + tr("Version: ") + version + "</p><p align=\"center\"><h3>" +
                       tr("Enable events sounds at the click of a button") +
                       "</h3></p><p align=\"center\"><a href=\"http://www.mepiscommunity.org/mx\">http://www.mepiscommunity.org/mx</a><br /></p><p align=\"center\">" +
                       tr("Copyright (c) MX Linux") + "<br /><br /></p>", 0, this);
    msgBox.addButton(tr("Cancel"), QMessageBox::AcceptRole); // because we want to display the buttons in reverse order we use counter-intuitive roles.
    msgBox.addButton(tr("License"), QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::RejectRole) {
        system("mx-viewer file:///usr/share/doc/mx-system-sounds/license.html '" + tr("MX System Sounds").toUtf8() + " " + tr("License").toUtf8() + "'");
    }
    this->show();
}

// Help button clicked
void mxsystemsounds::on_buttonHelp_clicked()
{
    this->hide();
    QString cmd = QString("mx-viewer http://www.mepiscommunity.org/user_manual_mx15/mxum.html#test '%1'").arg(tr("MX System Sounds"));
    system(cmd.toUtf8());
    this->show();
}


void mxsystemsounds::on_pushButton_customloginsound_clicked()
{
    this->hide();
    QString customloginsound = QFileDialog::getOpenFileName(this, tr("Select Sound File"), QString());
    QFileInfo file_info(customloginsound);
    ui->pushButton_customloginsound->setText(file_info.baseName());
    ui->pushButton_customloginsound->setToolTip(file_info.filePath());
    this->show();
}

void mxsystemsounds::on_pushButton_3_displaylogoutsound_clicked()
{
    this->hide();
    QString customlogoutsound = QFileDialog::getOpenFileName(this, tr("Select Sound File"), QString());
    QFileInfo file_info(customlogoutsound);
    ui->pushButton_3_displaylogoutsound->setText(file_info.baseName());
    ui->pushButton_3_displaylogoutsound->setToolTip(file_info.filePath());
    this->show();
}
