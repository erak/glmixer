/*
 * QLogStream.h
 *
 *  Created on: Jul 23, 2011
 *      Author: bh
 */

#ifndef QLOGSTREAM_H_
#define QLOGSTREAM_H_


#include <iostream>
#include <streambuf>
#include <string>

#include <QtGlobal>

class QLogStream : public std::basic_streambuf<char>
{
public:
	QLogStream(std::ostream &stream, QtMsgHandler msgHandlerFunction, QtMsgType messageType = QtDebugMsg) : m_stream(stream), msgHandler(msgHandlerFunction), msgType(messageType)
	{
		m_old_buf = stream.rdbuf();
		stream.rdbuf(this);
	}
	~QLogStream()
	{
		// output anything that is left
		if (!m_string.empty())
			msgHandler(msgType, m_string.c_str());

		m_stream.rdbuf(m_old_buf);
	}

protected:
	virtual int_type overflow(int_type v)
	{
		if (v == '\n')
		{
			msgHandler(msgType, m_string.c_str());
			m_string.erase(m_string.begin(), m_string.end());
		}
		else
			m_string += v;

		return v;
	}

	virtual std::streamsize xsputn(const char *p, std::streamsize n)
	{
		m_string.append(p, p + n);

		unsigned int pos = 0;
		while (pos != std::string::npos)
		{
			pos = m_string.find('\n');
			if (pos != std::string::npos)
			{
				std::string tmp(m_string.begin(), m_string.begin() + pos);
				msgHandler(msgType, tmp.c_str());
				m_string.erase(m_string.begin(), m_string.begin() + pos + 1);
			}
		}

		return n;
	}

private:
	std::ostream &m_stream;
	std::streambuf *m_old_buf;
	std::string m_string;
	QtMsgHandler msgHandler;
	QtMsgType msgType;
};


#endif /* QLOGSTREAM_H_ */
