// libTorrent - BitTorrent library
// Copyright (C) 2005, Jari Sundell
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// In addition, as a special exception, the copyright holders give
// permission to link the code of portions of this program with the
// OpenSSL library under certain conditions as described in each
// individual source file, and distribute linked combinations
// including the two.
//
// You must obey the GNU General Public License in all respects for
// all of the code used other than OpenSSL.  If you modify file(s)
// with this exception, you may extend this exception to your version
// of the file(s), but you are not obligated to do so.  If you do not
// wish to do so, delete this exception statement from your version.
// If you delete this exception statement from all source files in the
// program, then also delete it here.
//
// Contact:  Jari Sundell <jaris@ifi.uio.no>
//
//           Skomakerveien 33
//           3185 Skoppum, NORWAY

#ifndef LIBTORRENT_STORAGE_CHUNK_H
#define LIBTORRENT_STORAGE_CHUNK_H

#include <vector>
#include "chunk_part.h"

namespace torrent {

class Chunk : private std::vector<ChunkPart> {
public:
  typedef std::vector<ChunkPart>    Base;
  typedef std::pair<void*,uint32_t> MemoryArea;

  using Base::value_type;

  using Base::iterator;
  using Base::reverse_iterator;
  using Base::size;
  using Base::empty;

  using Base::begin;
  using Base::end;
  using Base::rbegin;
  using Base::rend;

  Chunk() : m_size(0), m_prot(0) {}
  ~Chunk() { clear(); }

  bool                is_all_valid() const;

  bool                is_readable() const             { return m_prot & MemoryChunk::prot_read; }
  bool                is_writable() const             { return m_prot & MemoryChunk::prot_write; }
  bool                has_permissions(int prot) const { return !(prot & ~m_prot); }

  uint32_t            size()                          { return m_size; }

  void                clear();

  iterator            at_position(uint32_t pos);
  MemoryArea          at_memory(uint32_t offset, iterator part);

  void                push_back(const MemoryChunk& c);

  // Check how much of the chunk is incore from pos.
  uint32_t            incore_length(uint32_t pos);

  bool                sync(int flags);

private:
  Chunk(const Chunk&);
  void operator = (const Chunk&);
  
  uint32_t            m_size;
  int                 m_prot;
};

}

#endif

  
