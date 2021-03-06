<?php

/**
 * @file
 * Contains SmartQueue.
 */

/**
 * Efficient query bundling database queue that disregards expired queue items.
 *
 * This backend drops items from the queue that have been sitting there twice as
 * long as the sites TTL is configured to. All load balancers that once had the
 * item in cache, are assumed to have already refreshed the item long ago.
 */
class AcquiaPurgeSmartQueue extends AcquiaPurgeEfficientQueue implements AcquiaPurgeQueueInterface {

  /**
   * Time in seconds Varnish is caching pages generated by Drupal.
   *
   * @var int
   */
  protected $ttl = 0;

  /**
   * Construct a AcquiaPurgeSmartQueue instance.
   *
   * @param AcquiaPurgeStateStorageInterface $state
   *   The state storage required for the queue counters.
   */
  public function __construct(AcquiaPurgeStateStorageInterface $state) {
    parent::__construct($state);
    $this->ttl = (int) variable_get('page_cache_maximum_age', 0);
  }

  /**
   * Expire queue items that should have already expired externally.
   */
  protected function expireQueueItems() {

    // Do not bother expiry under the following conditions.
    $expired = time() - (2 * $this->ttl);
    if ($this->ttl < 20) {
      return;
    }
    if (($expired < 1) || ($expired >= time())) {
      return;
    }

    // Delete items from the queue that expired and need no processing by AP.
    $deleted_items = db_delete('queue')
      ->condition('name', $this->name)
      ->condition('created', $expired, '<')
      ->execute();
    if ($deleted_items > 0) {
      watchdog(
        'acquia_purge',
        "Disregarded %n expired items from the queue (smart queue backend).",
        array('%n' => $deleted_items), WATCHDOG_INFO);
      $this->total()->decrease($deleted_items);
    }
  }

  /**
   * {@inheritdoc}
   */
  public function claimItem($lease_time = 30) {
    $this->expireQueueItems();
    return parent::claimItem($lease_time);
  }

  /**
   * {@inheritdoc}
   */
  public function claimItemMultiple($claims = 10, $lease_time = 30) {
    $this->expireQueueItems();
    return parent::claimItemMultiple($claims, $lease_time);
  }

}
