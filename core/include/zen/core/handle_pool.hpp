#pragma once

#include <cassert>
#include <cstdint>
#include <vector>

namespace zen {

namespace core {

using H = uint32_t;

template<typename T>
class HandlePool {
private:
	struct Slot {
		T object;
		bool active = false;
		uint32_t nextFree = 0;
	};

	std::vector<Slot> m_slots;
	uint32_t m_freeHead = 0;
	bool m_hasFree = false;

public:
	static const H kInvalid = __UINT32_MAX__;

	bool IsValid(H _handle) {
		return _handle != kInvalid;
	}

	template<typename U>
	[[nodiscard]] H alloc(U&& _obj) {
		// check for existing free slot 
		uint32_t idx;
		if (m_hasFree) {
			idx = m_freeHead;
			m_freeHead = m_slots[idx].nextFree;
			m_hasFree = (m_freeHead != idx);
		} else {
			idx = static_cast<uint32_t>(m_slots.size());
			m_slots.emplace_back();
		}
		
		// get slot and forward object
		auto& slot = m_slots[idx];
		slot.object = std::forward<U>(_obj);
		slot.active = true;
		return idx;
	}

	T* get(H _handle) {
		// validate handle
		if (!IsValid(_handle)) {
			return nullptr;
		}

		// check handle in range
		uint32_t idx = static_cast<uint32_t>(_handle);
		if (idx >= m_slots.size()) {
			return nullptr;
		}
		
		// get slot & check in use
		auto& slot = m_slots[idx];
		if (!slot.active) {
			return nullptr;
		}

		// return object ptr
		return &slot.object;
	}

	void free(H _handle) {
		// validate handle
		if (!IsValid(_handle)) {
			return;
		}

		// release release slot
		uint32_t idx = static_cast<uint32_t>(_handle);
		assert(idx < m_slots.size());
		auto& slot = m_slots[idx];
		assert(slot.active);
		slot.active = false;
		slot.nextFree = m_hasFree ? m_freeHead : idx;
		m_freeHead = idx;
		m_hasFree = true;
	}

};

} // namespace core

} // namespace zen
