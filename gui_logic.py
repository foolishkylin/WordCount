"""
    the logic part of gui
"""
import PyQt5.sip
import sys
from gui_base import Ui_MainWindow
from word_count import count_single_file, count_multiple_file
from PyQt5.QtWidgets import QApplication , QMainWindow, QFileDialog

file_fomats = ['C Files (*.c)', 'C++ Files (*.cpp)']
file_fomats_map = {
    'C Files (*.c)':0,
    'C++ Files (*.cpp)':1,
}

class Ui(Ui_MainWindow):
    ""
    def __init__(self, MainWindow):
        super(Ui, self).__init__(MainWindow)
        self.sf_button.clicked.connect(self.file_select)
        self.mf_button.clicked.connect(self.directory_select)
        self.sf_format.addItems(file_fomats)
        self.mf_format.addItems(file_fomats)

    def file_select(self):
        """

        :return:
        """
        filepath, filetype = QFileDialog.getOpenFileName(self,
                                                          "选取文件",
                                                          "./",
                                                          self.sf_format.currentText())  # 设置文件扩展名过滤,注意用双分号间隔
        self.sf_path.setText(filepath)
        text, cost = count_single_file(filepath)
        self.sf_browser.setText(text)

    def directory_select(self):
        """

        :return:
        """
        directory = QFileDialog.getExistingDirectory(self, "选取文件夹", "./")
        self.mf_path.setText(directory)
        dtext = count_multiple_file(directory, file_type=file_fomats_map[self.mf_format.currentText()])
        self.mf_browser.setText(dtext['text'])
        self.mf_number.setText(str(dtext['count_num']))




if __name__ == '__main__':
    '''
    主函数
    '''
    app = QApplication(sys.argv)
    mainWindow = QMainWindow()
    ui = Ui(mainWindow)
    mainWindow.show()
    sys.exit(app.exec_())