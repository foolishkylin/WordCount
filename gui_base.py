# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'wc.ui'
#
# Created by: PyQt5 UI code generator 5.12.3
#
# WARNING! All changes made in this file will be lost!

import sys
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtWidgets import QApplication , QMainWindow

class Ui_MainWindow(QtWidgets.QWidget):
    """
        the class of basic ui
    """
    def __init__(self, MainWindow):
        super(Ui_MainWindow, self).__init__()
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(628, 608)
        self.main_window = QtWidgets.QWidget(MainWindow)
        self.main_window.setBaseSize(QtCore.QSize(50, 50))
        self.main_window.setObjectName("main_window")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.main_window)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.tabWidget = QtWidgets.QTabWidget(self.main_window)
        self.tabWidget.setObjectName("tabWidget")
        self.sf_page = QtWidgets.QWidget()
        self.sf_page.setObjectName("sf_page")
        self.gridLayout = QtWidgets.QGridLayout(self.sf_page)
        self.gridLayout.setObjectName("gridLayout")
        self.sftext_fomat = QtWidgets.QLabel(self.sf_page)
        self.sftext_fomat.setObjectName("sftext_fomat")
        self.gridLayout.addWidget(self.sftext_fomat, 0, 2, 1, 1)
        self.sf_browser = QtWidgets.QTextBrowser(self.sf_page)
        self.sf_browser.setObjectName("sf_browser")
        self.gridLayout.addWidget(self.sf_browser, 3, 0, 1, 4)
        self.sfline = QtWidgets.QFrame(self.sf_page)
        self.sfline.setFrameShape(QtWidgets.QFrame.HLine)
        self.sfline.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.sfline.setObjectName("sfline")
        self.gridLayout.addWidget(self.sfline, 2, 0, 1, 4)
        self.sf_format = QtWidgets.QComboBox(self.sf_page)
        self.sf_format.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.sf_format.setInputMethodHints(QtCore.Qt.ImhNone)
        self.sf_format.setObjectName("sf_format")
        self.gridLayout.addWidget(self.sf_format, 0, 3, 1, 1)
        self.sf_button = QtWidgets.QPushButton(self.sf_page)
        self.sf_button.setObjectName("sf_button")
        self.gridLayout.addWidget(self.sf_button, 1, 3, 1, 1)
        self.stext_fp = QtWidgets.QLabel(self.sf_page)
        self.stext_fp.setObjectName("stext_fp")
        self.gridLayout.addWidget(self.stext_fp, 1, 0, 1, 1)
        self.sf_path = QtWidgets.QLabel(self.sf_page)
        self.sf_path.setObjectName("sf_path")
        self.gridLayout.addWidget(self.sf_path, 1, 1, 1, 2)
        self.tabWidget.addTab(self.sf_page, "")
        self.mf_page = QtWidgets.QWidget()
        self.mf_page.setObjectName("mf_page")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.mf_page)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.mf_browser = QtWidgets.QTextBrowser(self.mf_page)
        self.mf_browser.setObjectName("mf_browser")
        self.gridLayout_2.addWidget(self.mf_browser, 4, 0, 1, 4)
        self.mftext_fomat = QtWidgets.QLabel(self.mf_page)
        self.mftext_fomat.setObjectName("mftext_fomat")
        self.gridLayout_2.addWidget(self.mftext_fomat, 0, 2, 1, 1)
        self.mfline = QtWidgets.QFrame(self.mf_page)
        self.mfline.setFrameShape(QtWidgets.QFrame.HLine)
        self.mfline.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.mfline.setObjectName("mfline")
        self.gridLayout_2.addWidget(self.mfline, 2, 0, 1, 4)
        self.mftext_format = QtWidgets.QLabel(self.mf_page)
        self.mftext_format.setObjectName("mftext_format")
        self.gridLayout_2.addWidget(self.mftext_format, 3, 0, 1, 1)
        self.mf_format = QtWidgets.QComboBox(self.mf_page)
        self.mf_format.setObjectName("mf_format")
        self.gridLayout_2.addWidget(self.mf_format, 0, 3, 1, 1)
        self.mf_number = QtWidgets.QLabel(self.mf_page)
        self.mf_number.setObjectName("mf_number")
        self.gridLayout_2.addWidget(self.mf_number, 3, 1, 1, 1)
        self.mftext_fp = QtWidgets.QLabel(self.mf_page)
        self.mftext_fp.setObjectName("mftext_fp")
        self.gridLayout_2.addWidget(self.mftext_fp, 1, 0, 1, 1)
        self.mf_button = QtWidgets.QPushButton(self.mf_page)
        self.mf_button.setObjectName("mf_button")
        self.gridLayout_2.addWidget(self.mf_button, 1, 3, 1, 1)
        self.mf_path = QtWidgets.QLabel(self.mf_page)
        self.mf_path.setObjectName("mf_path")
        self.gridLayout_2.addWidget(self.mf_path, 1, 1, 1, 2)
        self.tabWidget.addTab(self.mf_page, "")
        self.horizontalLayout.addWidget(self.tabWidget)
        MainWindow.setCentralWidget(self.main_window)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 628, 26))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        """

        :param MainWindow:
        :return:
        """
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "源文件特征统计"))
        self.sftext_fomat.setText(_translate("MainWindow", "统计格式："))
        self.sf_button.setText(_translate("MainWindow", "选择文件"))
        self.stext_fp.setText(_translate("MainWindow", "文件路径"))
        self.sf_path.setText(_translate("MainWindow", "null"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.sf_page), _translate("MainWindow", "单文件统计"))
        self.mftext_fomat.setText(_translate("MainWindow", "统计格式："))
        self.mftext_format.setText(_translate("MainWindow", "文件个数："))
        self.mf_number.setText(_translate("MainWindow", "0"))
        self.mftext_fp.setText(_translate("MainWindow", "文件夹路径"))
        self.mf_button.setText(_translate("MainWindow", "选择文件夹"))
        self.mf_path.setText(_translate("MainWindow", "null"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.mf_page), _translate("MainWindow", "多文件统计"))




if __name__ == '__main__':
    '''
    主函数
    '''
    app = QApplication(sys.argv)
    mainWindow = QMainWindow()
    ui = Ui_MainWindow(mainWindow)
    mainWindow.show()
    sys.exit(app.exec_())