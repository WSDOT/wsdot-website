<?php

namespace Drupal\acquia_search;

/**
 * Class PreferredSearchCoreService.
 */
class PreferredSearchCoreService {

  /**
   * ExpectedCoreService constructor.
   *
   * @param string $acquia_identifier
   *   E.g. 'WXYZ-12345'.
   * @param string $ah_env
   *   E.g. 'dev', 'stage' or 'prod'.
   * @param string $sites_foldername
   *   E.g. 'default'.
   * @param string $ah_db_name
   *   E.g. 'my_site_db'.
   * @param mixed $available_cores
   *   E.g.
   *     [
   *       [
   *         'balancer' => 'useast11-c4.acquia-search.com',
   *         'core_id' => 'WXYZ-12345.dev.mysitedev',
   *       ],
   *     ].
   */
  public function __construct($acquia_identifier, $ah_env, $sites_foldername, $ah_db_name, $available_cores) {

    $this->acquia_identifier = $acquia_identifier;
    $this->ah_env = $ah_env;
    $this->sites_foldername = $sites_foldername;
    $this->ah_db_name = $ah_db_name;
    $this->available_cores = $available_cores;

  }

  /**
   * Returns expected core ID based on the current site configs.
   *
   * @return string
   *   Core ID.
   */
  public function getPreferredCoreId() {

    $core = $this->getPreferredCore();

    return $core['core_id'];

  }

  /**
   * Determines whether the expected core ID matches any available core IDs.
   *
   * The list of available core IDs is set by Acquia and comes within the
   * Acquia Subscription information.
   *
   * @return bool
   *   True if the expected core ID available to use with Acquia.
   */
  public function isPreferredCoreAvailable() {

    return (bool) $this->getPreferredCore();

  }

  /**
   * Returns the preferred core from the list of available cores.
   *
   * @return array|null
   *   NULL or
   *     [
   *       'balancer' => 'useast11-c4.acquia-search.com',
   *       'core_id' => 'WXYZ-12345.dev.mysitedev',
   *     ].
   */
  public function getPreferredCore() {

    $expected_cores = $this->getListOfPossibleCores();

    foreach ($expected_cores as $expected_core) {

      foreach ($this->available_cores as $available_core) {

        if ($expected_core == $available_core['core_id']) {

          return $available_core;

        }

      }

    }

  }

  /**
   * Returns URL for the preferred search core.
   *
   * @return string
   *   URL string, e.g.
   *   http://useast1-c1.acquia-search.com/solr/WXYZ-12345.dev.mysitedev
   */
  public function getPreferredCoreUrl() {

    $core = $this->getPreferredCore();

    return 'http://' . $core['balancer'] . '/solr/' . $core['core_id'];

  }

  /**
   * Returns a list of all possible search core IDs.
   *
   * The core IDs are generated based on the current site configuration.
   *
   * @return array
   *   E.g.
   *     [
   *       'WXYZ-12345',
   *       'WXYZ-12345.dev.mysitedev_folder1',
   *       'WXYZ-12345.dev.mysitedev_db',
   *     ]
   */
  public function getListOfPossibleCores() {

    $possible_core_ids = array();

    // In index naming, we only accept alphanumeric chars.
    $sites_foldername = preg_replace('@[^a-zA-Z0-9]+@', '', $this->sites_foldername);
    $ah_env = preg_replace('@[^a-zA-Z0-9]+@', '', $this->ah_env);

    if ($ah_env) {

      // When there is an Acquia DB name defined, priority is to pick
      // WXYZ-12345.[env].[db_name], then WXYZ-12345.[env].[site_foldername].
      // If we're sure this is prod, then 3rd option is WXYZ-12345.
      if ($this->ah_db_name) {
        $possible_core_ids[] = $this->acquia_identifier . '.' . $ah_env . '.' . $this->ah_db_name;
      }

      $possible_core_ids[] = $this->acquia_identifier . '.' . $ah_env . '.' . $sites_foldername;

      // @TODO: Support for [id]_[env][sitename] cores?
    }

    // For production-only, we allow auto-connecting to the suffix-less core
    // as the fallback.
    if (isset($_SERVER['AH_PRODUCTION']) || isset($_ENV['AH_PRODUCTION'])) {
      $possible_core_ids[] = $this->acquia_identifier;
    }

    return $possible_core_ids;

  }

}
