#ifndef MP_CONFIG_H
#define MP_CONFIG_H

#include <QString>
#include <QFont>
#include <QSize>
#include <QSettings>

namespace mp {

class Config : public QObject
{
	Q_OBJECT

public:
	static Config& Inst();

	QString UserId() const;
	QString Source() const;

	const QFont& DefaultFont() const;

	void SetVolume(qreal value);
	qreal Volume() const;

	void SetTVTabWindowSize(const QSize& size);
	QSize TVTabWindowSize() const;
	QSize RadioTabWindowSize() const;

signals:
	void VolumeChanged(qreal value);

private:
	void Load();

private:
	Config();
	static Config*		m_instance;

	QSettings			m_settings;
	QFont				m_defaultFont;
};

}

#endif