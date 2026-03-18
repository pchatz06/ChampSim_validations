#ifndef DRAM_STATS_H
#define DRAM_STATS_H

#include <cstdint>
#include <map>
#include <string>

struct dram_stats {
  std::string name{};
  long dbus_cycle_congested{};
  uint64_t dbus_count_congested = 0;
  uint64_t refresh_cycles = 0;
  unsigned WQ_ROW_BUFFER_HIT = 0, WQ_ROW_BUFFER_MISS = 0, RQ_ROW_BUFFER_HIT = 0, RQ_ROW_BUFFER_MISS = 0, WQ_FULL = 0;

  // Per-core stats — key is cpu ID (uint32_t, not uint8_t!)
  std::map<uint32_t, uint64_t> per_core_rq_dispatched;
  std::map<uint32_t, uint64_t> per_core_row_buffer_hit;
  std::map<uint32_t, uint64_t> per_core_row_buffer_miss;
  std::map<uint32_t, uint64_t> per_core_dbus_served;
  std::map<uint32_t, uint64_t> per_core_dbus_congested;
  std::map<uint32_t, uint64_t> per_core_rq_full;
  std::map<uint32_t, uint64_t> per_core_wq_full;
  std::map<std::pair<uint32_t, std::size_t>, uint64_t> per_core_bank_access;
  std::map<uint32_t, long> per_core_dbus_congestion_cycles;
  std::map<uint32_t, uint64_t> per_core_rq_admitted;
  std::map<uint32_t, uint64_t> per_core_wq_admitted;
  std::map<std::size_t, uint64_t> queue_position_rq_admitted;

  // NEW: tie + queue-wait stats
  uint64_t rr_tie_candidates = 0;
  uint64_t rr_tie_decisions = 0;
  std::map<uint32_t, uint64_t> per_core_rr_tie_wins;
  std::map<uint32_t, uint64_t> per_core_rr_tie_losses;

  std::map<uint32_t, uint64_t> per_core_qwait_sum;
  std::map<uint32_t, uint64_t> per_core_qwait_cnt;
};

dram_stats operator-(dram_stats lhs, dram_stats rhs);

#endif
