<?php

/**
 * Class WebformRedirectItem
 */

class WebformRedirectItem {

  /**
   * @var string
   */
  protected $defaultFallback;

  /**
   * @var string|null
   *
   */
  protected $defaultUrl;

  /**
   * @var WebformRedirectRule[]
   */
  protected $rules;

  public function __construct($default, $values) {
    $this->defaultFallback = $default['fallback'];
    $this->defaultUrl = isset($default['url']) ? $default['url'] : NULL;
    $this->rules = $this->getParsedRules($values);
  }

  public static function create($values) {
    return new static($values['default'], $values['rules']);
  }

  public function getDefaultFallback() {
    return $this->defaultFallback;
  }

  public function getRules() {
    return $this->rules;
  }

  public function getRulesCount() {
    return count($this->rules);
  }

  public function getDefaultUrl(){
    return $this->defaultUrl;
  }

  /**
   * @param string $id
   *   String rule id.
   *
   * @return null|WebformRedirectRule
   *    Rule if available. NULL otherwise.
   */
  public function getRuleById($id) {
    if (isset($this->rules[$id])) {
      return $this->rules[$id];
    }
    return NULL;
  }

  protected function getParsedRules($raw_rules) {
    $rules = array();
    foreach ($raw_rules as $key => $rule) {
      if (WebformRedirectRule::isValid($rule)) {
        $rules['redirect_rule_' . $key] = WebformRedirectRule::create($key, $rule);
      }
    }
    return $rules;
  }


}

class WebformRedirectRule {

  protected $id;

  protected $field;

  protected $value;

  protected $url;

  public function __construct($id, $field, $value, $url) {
    $this->id = $id;
    $this->field = $field;
    $this->value = $value;
    $this->url = $url;
  }

  public static function create($id, $rule_raw) {
    return new static(
      $id,
      $rule_raw['field'],
      $rule_raw['value'],
      $rule_raw['destination']
    );
  }

  /**
   * @param $rule_raw
   *
   * @return bool
   */
  public static function isValid($rule_raw) {
    $is_valid = FALSE;

    if (is_array($rule_raw)) {
      $is_valid = !empty($rule_raw['field']) && !empty($rule_raw['value']) && !empty($rule_raw['destination']);
    }
    return $is_valid;
  }

  /**
   * @return mixed
   */
  public function getField() {
    return $this->field;
  }

  /**
   * @return mixed
   */
  public function getValue() {
    return $this->value;
  }

  /**
   * @return mixed
   */
  public function getUrl() {
    return $this->url;
  }

}