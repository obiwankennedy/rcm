#ifndef TABLE_H
#define TABLE_H

#include <QString>

class Table
{
public:
    enum State {AVAILABLE,BUSY};
    Table();

    void setRoomName(QString);
    void setDescription(QString);
    void setId(int);
    void setCapacity(int c);
    void setState( bool);



    bool checkCapacity(int);

    QString getRoomName();
    QString getDescription();
    int getId();
    int getCapacity();
    State getCurrentState();
private:
    QString m_roomName;
    QString m_description;
    int m_id;
    int m_capacity;
    State m_state;

};

#endif // TABLE_H
