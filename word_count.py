#!/usr/bin/python
# -*- coding: UTF-8 -*-
import time
import os
import fnmatch
# file_path = 'sample/'

def count_single_file(file_path):
    """

    :param file_path:
    :return:
    """
    text = '文件: ' + file_path + '\n'
    start = time.perf_counter()
    fr = open(file_path)
    ltext = fr.readlines()
    dcount = {
        'cchar': 0,
        'cword': 0,
        'cline': len(ltext),
        'cempty_line': 0,
        'ccode_line': 0,
        'ccomment_line': 0,
        'cost_time':0.0
    }
    comment_block = False
    for line in ltext:
        dcount['cchar'] += len(line)
        dcount['cword'] += len(line.split(' '))

        if len(line.strip('\n')) <= 1:
            # check empty line
            dcount['cempty_line'] += 1
            continue

        code_check1 = line.split('//')[0]
        code_check2 = line.split('/*')[0]
        if len(code_check1.strip('\n')) > 1 or len(code_check2.strip('\n')) > 1:
            # check code line
            dcount['ccode_line'] += 1
            continue

        # check comment line
        if line.find('//') != -1:
            dcount['ccomment_line'] += 1
            continue
        if line.find('/*') != -1:
            comment_block = True
        if comment_block:
            # check "\**\"
            dcount['ccomment_line'] += 1
        if line.find('*/') != -1:
            comment_block = False

    dcount['cost_time'] = time.perf_counter() - start
    zh_names = ['字符数', '单词数', '总行数', '空行数', '代码行数', '注释行数', '耗时']
    en_names = ['cchar', 'cword', 'cline', 'cempty_line', 'ccode_line', 'ccomment_line', 'cost_time']
    for it in range(len(zh_names)):
        text += (zh_names[it] + ': ' + str(dcount[en_names[it]]))
        if it != len(zh_names) - 1:
            text += '\n'
        else:
            text += 's\n\n'

    return text, dcount['cost_time']

def count_multiple_file(directory, file_type=0):
    """

    :param directory:
    :param file_type:
    :return:
    """
    dtext = {
        'text': '',
        'count_num':0,
        'count_time':0.0
    }
    file_list = os.listdir(directory)
    print(file_list, file_type)
    file_filter = '*.c'
    if file_type == 1:
        file_filter = '*.cpp'
    for file in file_list:
         if fnmatch.fnmatch(file, file_filter):
             text, cost = count_single_file(directory + '/' + file)
             dtext['text'] += text
             dtext['count_time'] += cost
             dtext['count_num'] += 1
    dtext['text'] += '\n-----------------------------------------\n'
    dtext['text'] += ('总耗时： ' + str(dtext['count_time']) + 's\n')

    return dtext









