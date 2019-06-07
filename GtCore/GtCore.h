#ifndef __GT_CORE_H 
#define __GT_CORE_H 

#include <QString>
#include <QStringList>
#include <QImage>
#include <QColor>
#include <QByteArray>
#include <QPoint>
#include <QVariant>

#include <GtDefines.h>
// #include <GtDebug.h>

// Windows specific export and import specifications
#if defined(Q_OS_WIN)
#    define DLL_EXPORT __declspec(dllexport)
#    define DLL_IMPORT __declspec(dllimport)
#else
#    define DLL_EXPORT
#    define DLL_IMPORT
#endif
#ifdef EXPORT
# undef EXPORT
#endif

#ifdef EXPORT 
# undef EXPORT
#endif
#ifdef BUILDING_GTCORE
# define EXPORT DLL_EXPORT
#else
# define EXPORT DLL_IMPORT
#endif

extern EXPORT QString platformString ();
extern EXPORT QString memText (qint64 si);
extern EXPORT QString progressPercent (qint64 n, qint64 si);
extern EXPORT void msleep (unsigned long l);

class GtProgress;

extern EXPORT QByteArray  readGZipFile (const QString &fn);
extern EXPORT QByteArray  readZipFile  (const QString &fn);
extern EXPORT bool        writeZipFile (const QString &fn, const QByteArray& a);
extern EXPORT QVariant    readGZipJson (const QString &fn);
extern EXPORT QVariant    parseJson    (const QByteArray& a);
extern EXPORT QByteArray  createJson   (const QVariant& a);
extern EXPORT QVariant    readJson     (const QString & fn);
extern EXPORT QVariant    parseProFile (const QString & fn);
extern EXPORT bool        writeJson    (const QVariant& a, const QString& fn);
extern EXPORT QStringList extractFilesFromQrc  (const QString& fn);

extern EXPORT int         char2hex (QChar a);
extern EXPORT QString     replaceStrangeChars (const QString &s); 
extern EXPORT QColor      randomColor ();

extern EXPORT int          countLines (const QByteArray& b);
extern EXPORT QVector<int> sortRanks (const QStringList & b);
extern EXPORT quint64      stringValue (const QString & fn);

inline int color2gray(const QColor&c) {return (25*c.red()+60*c.green()+15*c.blue()) / 100;};


#endif

