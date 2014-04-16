#include "RadioPageController.h"
#include "RadioPage.h"
#include "AudioStream.h"
#include "Path.h"

namespace mp {

RadioPageController::RadioPageController()
	:m_view(NULL)
	,m_audioStream(new AudioStream())
{
	ReLoadData();

	m_view = new RadioPage(NULL, &m_radioGenres, &m_stations, &m_topSations, &m_lastSations);

	connect(m_view, SIGNAL(PlayRadio(const QString&)), this, SLOT(PlayRadio(const QString&)));
	connect(m_view, SIGNAL(GenreChanged(const QString&)), this, SLOT(GenreChanged(const QString&)));
	connect(m_view, SIGNAL(TopStationslUpdated()), this, SLOT(TopStationslUpdated()));
	connect(m_view, SIGNAL(PauseRadio()), this, SLOT(PauseRadio()));

	//TopStationslUpdated();
	//m_view->UpdateCurrentGenreStations(&m_stations);
	//m_view->UpdateLastStations(&m_lastSations);
	//m_view->GenreModelUpdated(&m_radioGenres);
	//m_view->Init();
	
	qDebug() << "Radio widget created";
}

RadioPageController::~RadioPageController()
{
	
}


void RadioPageController::ReLoadData()
{
	m_radioGenres.Load(ConfigFilePath("radiogenres.json"));
	m_stations.Load(ConfigFilePath("radio.json"));
}

TabPage* RadioPageController::View()
{
	return m_view;
}


void RadioPageController::PlayRadio(const QString& id)
{
	ChannelSourcePtr channel = m_stations.FindById(id);
	if(channel)
	{
		m_audioStream->SetUrl(channel->Url());
		m_audioStream->Play();

		// Update last staions with new  channel
		LastStationsUpdated(channel);
	}
	else
	{
		qDebug() << "PlayRadio: station doesn't found, id: \"" << id << "\"";
	}
}

void RadioPageController::PauseRadio()
{
	m_audioStream->Pause();
}

void RadioPageController::GenreChanged(const QString& id)
{
	//m_currentSations.Cleanup();

	foreach(ChannelSourcePtr channel, m_stations.Items())
	{
		// Genre id
		QString currentGenreId = channel->GenreId();//index.data(ChannelSourceModel::GenreId).toString();;
		if(currentGenreId.isEmpty())
		{
			GenreItemPtr genre = m_radioGenres.FindById(id);

			if(!genre.isNull())
			{
				currentGenreId = genre->Id();
			}
		}

		// Channel id
		QString channelId = channel->Id();//index.data(ChannelSourceModel::Id).toString();

		if(!currentGenreId.isEmpty() && !channelId.isEmpty())
		{
			if(currentGenreId == id)
			{
				ChannelSourcePtr channel = m_stations.FindById(channelId);
				m_currentSations.Add(channel, true);
			}
		}
	}

	//m_view->UpdateCurrentGenreStations(&m_currentSations);
}

void RadioPageController::TopStationslUpdated()
{
	//m_topSations.Cleanup();
	//m_view->UpdateTopStations(&m_topSations);
}

void RadioPageController::LastStationsUpdated(ChannelSourcePtr newchannel)
{
	/*
	int rows = m_lastSations.rowCount();
	if(rows <= 2)
	{
		m_lastSations.Add(newchannel, true);
	}
	else
	{
		m_lastSations.removeRow(2);
		m_lastSations.Add(newchannel, true);
	}

	m_view->UpdateLastStations(&m_lastSations);
	*/
}

}