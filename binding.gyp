{
  'targets': [
    {
      'target_name': 'qt',
      'sources': [
        'src/qt.cc', 

        'src/QtCore/qsize.cc',
        'src/QtCore/qpointf.cc',

        'src/QtGui/qapplication.cc',
        'src/QtGui/qwidget.cc',
        'src/QtGui/qmouseevent.cc',
        'src/QtGui/qkeyevent.cc',
        'src/QtGui/qpixmap.cc',
        'src/QtGui/qpainter.cc',
        'src/QtGui/qcolor.cc',
        'src/QtGui/qbrush.cc',
        'src/QtGui/qpen.cc',
        'src/QtGui/qimage.cc',
        'src/QtGui/qpainterpath.cc',
        'src/QtGui/qfont.cc',
        'src/QtGui/qmatrix.cc',
        'src/QtGui/qsound.cc',
        'src/QtGui/qscrollarea.cc',
        'src/QtGui/qscrollbar.cc',

        'src/QtTest/qtesteventlist.cc'
      ],
      'conditions': [
        ['OS=="mac"', {
          'include_dirs': [
            'deps/qt-4.8.0/darwin/x64/include',
            'deps/qt-4.8.0/darwin/x64/include/QtCore',
            'deps/qt-4.8.0/darwin/x64/include/QtGui',
            'deps/qt-4.8.0/darwin/x64/include/QtTest'
          ],
          'libraries': [
            # TODO: fix node-gyp behavior that requires ../
            '../deps/qt-4.8.0/darwin/x64/lib/QtCore.framework/QtCore', 
            '../deps/qt-4.8.0/darwin/x64/lib/QtGui.framework/QtGui', 
            '../deps/qt-4.8.0/darwin/x64/lib/QtTest.framework/QtTest'
          ],
        }],
        ['OS=="linux"', {
          'cflags': [
            '<!@(pkg-config --cflags QtCore QtGui QtTest)'
          ],
          'ldflags': [
            '<!@(pkg-config --libs-only-L --libs-only-other QtCore QtGui QtTest)'
          ],
          'libraries': [
            '<!@(pkg-config --libs-only-l QtCore QtGui QtTest)'
          ]
        }],
        ['OS=="win"', {
          'include_dirs': [
              'deps/qt-4.8.0/win32/ia32/include',
              'deps/qt-4.8.0/win32/ia32/include/QtCore',
              'deps/qt-4.8.0/win32/ia32/include/QtGui',
              'deps/qt-4.8.0/win32/ia32/include/QtTest',
          ],
          'libraries': [
              # TODO: fix node-gyp behavior that requires ../
              '../deps/qt-4.8.0/win32/ia32/lib/QtCore4.lib',
              '../deps/qt-4.8.0/win32/ia32/lib/QtGui4.lib',
              '../deps/qt-4.8.0/win32/ia32/lib/QtTest4.lib'
          ]
        }]        
      ]
    }
  ]
}
