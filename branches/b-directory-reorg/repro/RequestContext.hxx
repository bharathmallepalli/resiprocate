#if !defined(RESIP_REQUEST_CONTEXT_HXX)
#define RESIP_REQUEST_CONTEXT_HXX 

#include <vector>
#include <iosfwd>
#include "resip/stack/Uri.hxx"
#include "repro/RequestProcessorChain.hxx"
#include "repro/ResponseContext.hxx"
#include "resip/stack/NameAddr.hxx"
#include "repro/ResponseContext.hxx"

namespace resip
{
class SipMessage;
class TransactionTerminated;
}

namespace repro
{
class Proxy;

class RequestContext
{
   public:
      RequestContext(Proxy& proxy,
                     RequestProcessorChain& chain);
      virtual ~RequestContext();

      void process(resip::TransactionTerminated& msg);
      void process(std::auto_ptr<resip::Message> msg);
      
      /// Returns the SipMessage associated with the server transaction
      resip::SipMessage& getOriginalRequest();
      const resip::SipMessage& getOriginalRequest() const;
      const resip::Data& getTransactionId() const;
      
      /** Returns the event that we are currently working on. Use a pointer
          since users need to check for null */
      resip::Message* getCurrentEvent();
      const resip::Message* getCurrentEvent() const;
      
      void setDigestIdentity (const resip::Data&);
      const resip::Data& getDigestIdentity() const;

      void pushChainIterator(RequestProcessorChain::Chain::iterator&);
      RequestProcessorChain::Chain::iterator popChainIterator();
      bool chainIteratorStackIsEmpty();

      Proxy& getProxy();
      void sendResponse(const resip::SipMessage& response);
      
      void addTarget(const resip::NameAddr& target);
      std::vector<resip::NameAddr>& getCandidates();
      
   private:
      resip::SipMessage*  mOriginalRequest;
      resip::Message*  mCurrentEvent;
      RequestProcessorChain& mRequestProcessorChain;
      resip::Data mDigestIdentity;
      std::vector<resip::NameAddr> mCandidateTargets;
      int mTransactionCount;
      Proxy& mProxy;
      bool mHaveSentFinalResponse;
      ResponseContext mResponseContext;

      typedef std::vector<RequestProcessorChain::Chain::iterator>

      /** Stack of iterators used to keep track of where
          we are in the request processor chain(s) for
          async processing */
      ChainIteratorStack;
      ChainIteratorStack mChainIteratorStack;
      
      void fixStrictRouterDamage();
      void removeTopRouteIfSelf();
      
      friend class ResponseContext;
      friend std::ostream& operator<<(std::ostream& strm, const repro::RequestContext& rc);
};

std::ostream&
operator<<(std::ostream& strm, const repro::RequestContext& rc);


}

#endif

/* ====================================================================
 * The Vovida Software License, Version 1.0 
 * 
 * Copyright (c) 2000 Vovida Networks, Inc.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * 3. The names "VOCAL", "Vovida Open Communication Application Library",
 *    and "Vovida Open Communication Application Library (VOCAL)" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact vocal@vovida.org.
 *
 * 4. Products derived from this software may not be called "VOCAL", nor
 *    may "VOCAL" appear in their name, without prior written
 *    permission of Vovida Networks, Inc.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL VOVIDA
 * NETWORKS, INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT DAMAGES
 * IN EXCESS OF $1,000, NOR FOR ANY INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * 
 * ====================================================================
 * 
 * This software consists of voluntary contributions made by Vovida
 * Networks, Inc. and many individuals on behalf of Vovida Networks,
 * Inc.  For more information on Vovida Networks, Inc., please see
 * <http://www.vovida.org/>.
 *
 */