#!/usr/bin/python
# -*- coding: UTF-8 -*-
import time
file_path = 'sample/'

def count_single_file(file_name):
    """

    :param file_name:
    :return:
    """
    start = time.perf_counter()
    fr = open(file_path + file_name)
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

    return dcount









