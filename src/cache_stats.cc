#include "cache_stats.h"

cache_stats operator-(cache_stats lhs, cache_stats rhs)
{
  cache_stats result;
  result.pf_requested = lhs.pf_requested - rhs.pf_requested;
  result.pf_issued = lhs.pf_issued - rhs.pf_issued;
  result.pf_useful = lhs.pf_useful - rhs.pf_useful;
  result.pf_useless = lhs.pf_useless - rhs.pf_useless;
  result.pf_fill = lhs.pf_fill - rhs.pf_fill;

  result.hits = lhs.hits - rhs.hits;
  result.misses = lhs.misses - rhs.misses;

  result.total_miss_latency_cycles = lhs.total_miss_latency_cycles - rhs.total_miss_latency_cycles;

  auto sub_map = [](const std::map<uint32_t, uint64_t>& a,
                    const std::map<uint32_t, uint64_t>& b) {
    std::map<uint32_t, uint64_t> out;
    for (const auto& [k, v] : a) {
      auto it = b.find(k);
      out[k] = v - (it != b.end() ? it->second : 0ULL);
    }
    return out;
  };

  result.writebacks_per_cpu = sub_map(lhs.writebacks_per_cpu, rhs.writebacks_per_cpu);
  result.collisions_to_wq_per_cpu = sub_map(lhs.collisions_to_wq_per_cpu, rhs.collisions_to_wq_per_cpu);

  return result;
}
