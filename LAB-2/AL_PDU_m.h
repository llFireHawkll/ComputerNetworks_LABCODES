//
// Generated file, do not edit! Created by nedtool 5.2 from AL_PDU.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __AL_PDU_M_H
#define __AL_PDU_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0502
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>AL_PDU.msg:17</tt> by nedtool.
 * <pre>
 * packet AL_PDU
 * {
 *     int id;
 *     int msg;
 *     int srcAdd;
 *     int destAdd;
 * }
 * </pre>
 */
class AL_PDU : public ::omnetpp::cPacket
{
  protected:
    int id;
    int msg;
    int srcAdd;
    int destAdd;

  private:
    void copy(const AL_PDU& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const AL_PDU&);

  public:
    AL_PDU(const char *name=nullptr, short kind=0);
    AL_PDU(const AL_PDU& other);
    virtual ~AL_PDU();
    AL_PDU& operator=(const AL_PDU& other);
    virtual AL_PDU *dup() const override {return new AL_PDU(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getId() const;
    virtual void setId(int id);
    virtual int getMsg() const;
    virtual void setMsg(int msg);
    virtual int getSrcAdd() const;
    virtual void setSrcAdd(int srcAdd);
    virtual int getDestAdd() const;
    virtual void setDestAdd(int destAdd);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AL_PDU& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AL_PDU& obj) {obj.parsimUnpack(b);}


#endif // ifndef __AL_PDU_M_H

